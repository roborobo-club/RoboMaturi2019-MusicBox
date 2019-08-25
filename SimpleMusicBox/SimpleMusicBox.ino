/*******************************************************************************
 * ロボロボ・CLUB 夏祭り2019 電子工作ワークショップ「オルゴール」
 *******************************************************************************/

// 各音階で鳴らす周波数(ヘルツ)
enum ToneFreq {
  TONE_REST = 0,            // 休止符 (音を再生しない)
  TONE_DO1 = 262,           // ド
  TONE_RE1 = 294,           // レ
  TONE_MI1 = 330,           // ミ
  TONE_FA1 = 349,           // ファ
  TONE_SO1 = 392,           // ソ
  TONE_LA1 = 440,           // ラ
  TONE_SI1 = 494,           // シ
  TONE_DO2 = TONE_DO1 * 2,  // 高いド
  TONE_RE2 = TONE_RE1 * 2,  // 高いレ
  TONE_MI2 = TONE_MI1 * 2,  // 高いミ
  TONE_FA2 = TONE_FA1 * 2,  // 高いファ
  TONE_SO2 = TONE_SO1 * 2,  // 高いソ
  TONE_LA2 = TONE_LA1 * 2,  // 高いラ
  TONE_SI2 = TONE_SI1 * 2,  // 高いシ
};

// 各音符を再生する時間(ミリ秒)
enum Duration {
  DUR_1 = 2000,             // 全音符の長さ
  DUR_2 = DUR_1 / 2,        // 2分音符
  DUR_4 = DUR_1 / 4,        // 4分音符
  DUR_8 = DUR_1 / 8,        // 8分音符
  DUR_16 = DUR_1 / 16,      // 16分音符
  DUR_32 = DUR_1 / 32,      // 32分音符
};

const int DUR_GAP = 15;     // 音符と音符の間に挟む微小時間 [ms]

// 音符1つ分を表す型
struct Note {
  ToneFreq frequency;       // 音階の周波数 [Hz]
  Duration duration;        // 音を鳴らす長さ [ms]
};


////////////////////////////////////////////////////////////////////////////////
//
// 楽譜(音符の配列変数) 「きらきら星」
//
////////////////////////////////////////////////////////////////////////////////
const Note music[] = {
  {TONE_DO2, DUR_4},
  {TONE_DO2, DUR_4},
  {TONE_SO2, DUR_4},
  {TONE_SO2, DUR_4},
  {TONE_LA2, DUR_4},
  {TONE_LA2, DUR_4},
  {TONE_SO2, DUR_2},

  {TONE_FA2, DUR_4},
  {TONE_FA2, DUR_4},
  {TONE_MI2, DUR_4},
  {TONE_MI2, DUR_4},
  {TONE_RE2, DUR_4},
  {TONE_RE2, DUR_4},
  {TONE_DO2, DUR_2},

  {TONE_SO2, DUR_4},
  {TONE_SO2, DUR_4},
  {TONE_FA2, DUR_4},
  {TONE_FA2, DUR_4},
  {TONE_MI2, DUR_4},
  {TONE_MI2, DUR_4},
  {TONE_RE2, DUR_2},

  {TONE_SO2, DUR_4},
  {TONE_SO2, DUR_4},
  {TONE_FA2, DUR_4},
  {TONE_FA2, DUR_4},
  {TONE_MI2, DUR_4},
  {TONE_MI2, DUR_4},
  {TONE_RE2, DUR_2},

  {TONE_DO2, DUR_4},
  {TONE_DO2, DUR_4},
  {TONE_SO2, DUR_4},
  {TONE_SO2, DUR_4},
  {TONE_LA2, DUR_4},
  {TONE_LA2, DUR_4},
  {TONE_SO2, DUR_2},

  {TONE_FA2, DUR_4},
  {TONE_FA2, DUR_4},
  {TONE_MI2, DUR_4},
  {TONE_MI2, DUR_4},
  {TONE_RE2, DUR_4},
  {TONE_RE2, DUR_4},
  {TONE_DO2, DUR_2},
};


const int LED_PIN[4] = {9, 10, 11, 12};                   // 4つのLEDにつないでいるピン番号
const int SPEAKER_PIN = 6;                                // スピーカーに繋いでいるピン番号
const int musicLength = sizeof(music) / sizeof(music[0]); // 再生する音楽の長さ(musicの要素数)

void setup() {
  // 各LEDのピンの初期化
  pinMode(LED_PIN[0], OUTPUT);
  pinMode(LED_PIN[1], OUTPUT);
  pinMode(LED_PIN[2], OUTPUT);
  pinMode(LED_PIN[3], OUTPUT);
}

int count = 0;
void loop() {
  // 明るさが一定値以上になるまでは鳴らさない
  while (analogRead(A0) <= 80) {
    count = 0;
  }
  // 一度再生し終えたらカウンタをリセットし、再び暗くなるまで鳴らさない
  if (musicLength <= count) {
    count = 0;
    while (analogRead(A0) > 80); // この行を消すとループして再生するようになる
  }

  digitalWrite(LED_PIN[count % 4], HIGH);
  
  if (music[count].frequency > 0) {
    tone(SPEAKER_PIN, music[count].frequency, music[count].duration - DUR_GAP);
  }
  delay(music[count].duration);

  digitalWrite(LED_PIN[count % 4], LOW);
  
  count += 1;
}
