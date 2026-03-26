unsigned char xpin1 = 32;
unsigned char ypin2 = 33;

int adc1raw;
int adc2raw;

int minimal1, maximal1, minimal2, maximal2;

float av1, av2, df1, df2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  minimal1 = analogRead(xpin1);
  maximal1 = analogRead(xpin1);
  minimal2 = analogRead(ypin2);
  maximal2 = analogRead(ypin2);
}

void loop() {
  // put your main code here, to run repeatedly:
  adc1raw = analogRead(xpin1);
  adc2raw = analogRead(ypin2);

  //Serial.println("=========");
  //Serial.print("ADC1: "); Serial.println(adc1raw);
  //Serial.print("ADC2: "); Serial.println(adc2raw);

  minimal1 = min(minimal1, adc1raw);
  maximal1 = max(maximal1, adc1raw);
  minimal2 = min(minimal2, adc2raw);
  maximal2 = max(maximal2, adc2raw);

  Serial.println("=======");
  //Serial.print("ADC1 -> MIN: "); Serial.print(minimal1); Serial.print("  |  MAX: "); Serial.println(maximal1);
  //Serial.print("ADC2 -> MIN: "); Serial.print(minimal2); Serial.print("  |  MAX: "); Serial.println(maximal2);

  av1 = (minimal1 + maximal1)/2;
  av2 = (minimal2 + maximal2)/2;

  df1 = max(abs(av1-minimal1), abs(av1-maximal1));
  df2 = max(abs(av2-minimal2), abs(av2-maximal2));

  Serial.print("AV1: "); Serial.print(av1); Serial.print("  |  DF1: "); Serial.println(df1);
  Serial.print("AV2: "); Serial.print(av2); Serial.print("  |  DF2: "); Serial.println(df2);

}
