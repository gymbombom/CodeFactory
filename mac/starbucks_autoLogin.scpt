--터미널 열고 커맨드 실행
tell application "Terminal"
	do script "networksetup -setairportnetwork en0 KT_starbucks"
end tell

delay 15  --15초 딜레이

tell application "System Events"
	key code 53.  --ESC 키 입력
end tell

tell application "Google Chrome". --구글 크롬 활성화
	activate
	
	tell window 1
		set newTab to make new tab with properties {URL:"http://www.naver.com/"}. --첫번째 윈도우 열고 URL 입력
	end tell
	delay 1
	
	tell application "System Events"
		delay 1
		
		repeat 5 times    --tab 5번 입력
			keystroke tab
			delay 0.5
		end repeat
		
		key code 49  --Space Bar 입력
		delay 0.5
		
		repeat 3 times. --Tab 3번 입력
			keystroke tab
			delay 0.5
		end repeat
		delay 0.5
		
		keystroke return
		delay 1
		keystroke "leeilkyu"
		delay 0.5
		keystroke tab
		delay 0.5
		keystroke "dlfrb2002@gmail.com"
		delay 0.5
		
		repeat 5 times
			keystroke tab
			delay 0.5
		end repeat
		
		key code 49. --Space Bar 입력
		delay 0.5
		keystroke tab
		delay 0.5
		key code 49. --Space Bar 입력
		delay 0.5
		keystroke tab
		delay 0.5
		keystroke tab
		delay 0.5
		keystroke return
	end tell
end tell

