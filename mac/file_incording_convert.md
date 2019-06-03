
--  파일 인코딩을 euc-kr 에서 utf-8로변경
iconv -c -f euc-kr -t utf-8  euc-kr_textfile.txt > utf-8_dest_textfile.txt
