#include <DHT.h>
#define DHT_PIN 4
#define LED_BOARD_PIN 2
#define BLINKER_WIFI
#include <Blinker.h>

DHT dht(DHT_PIN, DHT11);

char auth[] = "5e70a97241c5";
char ssid[] = "Xiaomi 17 Pro";
char pswd[] = "eatordie";

BlinkerNumber Number1("TempC");
BlinkerNumber Number2("TempF");

// ---------------- 卡尔曼滤波变量与函数 ----------------
float kalman_est;
float kalman_err;
float kalman_Q;
float kalman_R;

void kalmanInit(float initVal, float initErr, float q, float r) {
  kalman_est = initVal;
  kalman_err = initErr;
  kalman_Q = q;
  kalman_R = r;
}

float kalmanUpdate(float measurement) {
  float pred_err = kalman_err + kalman_Q;
  float K = pred_err / (pred_err + kalman_R);
  kalman_est = kalman_est + K * (measurement - kalman_est);
  kalman_err = (1 - K) * pred_err;
  return kalman_est;
}
// ---------------- 非阻塞定时变量 ----------------
unsigned long previousSensorMillis = 0; // 上一次传感器采样的时间
const long sensorInterval = 15000;       // 传感器采样间隔（15秒）
unsigned long previousBlinkMillis = 0;  // 上一次LED闪烁的时间
bool ledState = LOW;                    // LED当前状态（用于闪烁）

void setup() {
  Serial.begin(115200);
  pinMode(LED_BOARD_PIN, OUTPUT);
  digitalWrite(LED_BOARD_PIN, LOW); // 确保LED初始熄灭

  BLINKER_DEBUG.stream(Serial);
  Blinker.begin(auth, ssid, pswd);

  dht.begin();

  // 启动动画
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BOARD_PIN, HIGH); delay(200);
    digitalWrite(LED_BOARD_PIN, LOW);  delay(200);
  }

  float firstTemp = dht.readTemperature();
  // 如果首次读取失败，使用一个合理的默认值（例如25.0）初始化
  if (isnan(firstTemp)) {
    firstTemp = 25.0;
    Serial.println("⚠️  首次传感器读取失败，使用默认值25.0℃初始化滤波器。");
  }
  kalmanInit(firstTemp, 1.0, 0.1, 5.0);

  Serial.println("\n🌡️  ESP32环境监测仪启动");
  Serial.println("==========================");
  Serial.println("系统启动，开始滤波与上云...");
}

void loop() {
  // 核心1：必须始终维持Blinker连接心跳
  Blinker.run();

  // 核心2：非阻塞定时-传感器采样与处理（每3秒一次）
  unsigned long currentMillis = millis();
  if (currentMillis - previousSensorMillis >= sensorInterval) {
    previousSensorMillis = currentMillis; // 重置计时器

    // 读取传感器
    float rawTemp = dht.readTemperature();
    float rawHumi = dht.readHumidity();

    // 处理读取失败的情况
    if (isnan(rawTemp) || isnan(rawHumi)) {
      Serial.println("❌ [" + String(currentMillis/1000) + "s] 传感器读取失败，跳过本次数据。");
      digitalWrite(LED_BOARD_PIN, HIGH); // 快速闪烁一次指示错误
      delay(50);
      digitalWrite(LED_BOARD_PIN, LOW);
      // 注意：此处不return，而是跳过数据处理，维持系统运行
    } else {
      // 正常情况：进行滤波和数据上传
      float filteredTemp = kalmanUpdate(rawTemp);

      // 控制台输出（格式化，清晰易读）
      Serial.println("--- [" + String(currentMillis/1000) + "s] ---");
      Serial.print("RAW: "); Serial.print(rawTemp); Serial.print("°C | ");
      Serial.print("FILTERED: "); Serial.print(filteredTemp); Serial.println("°C");

      // 上传到Blinker（两个数据流）
      Number1.print(rawTemp);
      Number2.print(filteredTemp);

      // 简单的LED温度指示
      if (rawTemp > 28.0) {
        digitalWrite(LED_BOARD_PIN, HIGH); // 高温警告
      } else {
        digitalWrite(LED_BOARD_PIN, LOW);  // 正常温度
      }
    }
  }

}
