(*스타벅스 starbucks 자동 로그인 스크립트 *)
--스타벅스 로그인 페이지 변경으로 사용불가

--터미널 열고 명령어 입력
tell application "Terminal"
	do script "networksetup -setairportnetwork en0 KT_starbucks"
end tell

delay 15 --15초 딜레이

tell application "System Events"
	key code 53. --ESC 키입력
end tell

--safari 열기
tell application "Google Chrome"
	activate
	
	tell window 1
		set newTab to make new tab with properties {URL:"http://www.naver.com/"}
	end tell
	delay 1
	
	tell application "System Events"
		delay 1
		
		repeat 5 times
			keystroke tab
			delay 0.5
		end repeat
		
		key code 49
		delay 0.5
		
		repeat 3 times
			keystroke tab
			delay 0.5
		end repeat
		delay 0.5
		
		keystroke return
		delay 1
		keystroke "name"
		delay 0.5
		keystroke tab
		delay 0.5
		keystroke "test@gmail.com"
		delay 0.5
		
		repeat 5 times
			keystroke tab
			delay 0.5
		end repeat
		
		key code 49
		delay 0.5
		keystroke tab
		delay 0.5
		key code 49
		delay 0.5
		keystroke tab
		delay 0.5
		keystroke tab
		delay 0.5
		keystroke return
	end tell
end tell
