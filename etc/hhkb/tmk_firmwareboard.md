# HHKB(해피해킹) tmk 펌웨어board 세팅방벙 
[TMK Keymap Editor](http://www.tmk-kbd.com/tmk_keyboard/editor/index.html)
```shell
# 펌웨어 Build 도구 설치
#Mac os 의 경우
brew tap osx-cross/avr
brew install avr-gcc
brew install dfu-programmer
```


```shell
#  firmware Build 방법
# atmega32u4(for HHKB/FC660C/FC980C Alt Controllers and USB-USB Conveter
# atmega32u2(for other Converters and Alps64)
# controller = atmega32u4  <hhkb pro2의 경우>
dfu-programmer <controller> erase --force
dfu-programmer <controller> flash <your_firmware.hex>
dfu-programmer <controller> reset
```

action_layer_tab_key

