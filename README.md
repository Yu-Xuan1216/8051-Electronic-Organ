# eOrgan - 8051 Electronic Organ

## 專案介紹
eOrgan (Electronic Organ) 是一個基於8051微處理器的簡易電子琴系統。
使用者可以透過 4x4 keyboard 彈奏音符，並輸出聲音，七段顯示器提供錄音與播放狀態指示。

![8051](https://github.com/user-attachments/assets/a64a1744-7585-4b2d-81c7-f3b79c5f16db)

## 功能
- 音符彈奏：按鍵對應不同音高 (C, C#, D, D#, E, F, F#, G, G#, A, A#, B, B, high C, high D)
- 錄音功能：記錄使用者的彈奏音符與節拍
- 播放功能：依照錄音內容播放音符，並維持原始節拍  
- 狀態指示：七段顯示器顯示目前模式（0: 錄音, 1: 播放）
- 定時控制：  
  - Timer0: 輸出音符 
  - Timer1: 控制拍子與播放節奏

## 專案結構
- 主程式 (eOrgan-108328017.c)
  - 控制電子琴的錄音、播放與音符輸出
  - 使用Timer0產生蜂鳴器方波聲音
  - 使用Timer1控制拍子與播放節奏
  - 錄音資料存於 record[] 陣列中
- 鍵盤操作 (Keypad4x4.c / Keypad4x4.h)
  - Keyboard 掃描與按鍵的對應
- Makefile
  - 編譯 Keypad4x4.c 成 .rel 檔案
  - 生成靜態函式庫 myIO.lib
  - 編譯主程式並連結函式庫，生成 .hex 可燒錄檔

## 操作方式
- 音符彈奏: 直接按下按鍵可發出特定音符的聲音
- 錄音模式: 按下 E，七段顯示器會顯示 **0**，代表開始錄音
- 播放模式: 按下 F，七段顯示器顯示 **1**，並播放已錄製的旋律

## 編譯與執行
```shell=
make
```
