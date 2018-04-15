# HHKB tmk board setting 


```shell
# 펌웨어 Build 도구 설치
brew tap osx-cross/avr
brew install avr-gcc
brew install dfu-programmer
```


```shell
#  firmware Build 방법
# controller = atmega32 <hhkb 키보드>
dfu-programmer <controller> erase --force
dfu-programmer <controller> flash <your_firmware.hex>
dfu-programmer <controller> reset
```

action_layer_tab_key

