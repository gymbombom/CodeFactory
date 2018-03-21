# 맥 -> Window 파일전송시 파일이름 깨짐 현상 해결방법
> Mac OS 와 Windows 가 서로 다른 Unicode Nomalization Form 을 사용하기 때문에 발생하는 문제 (ex : ㅎㅏㄴㄱㅡㄹ.docx)

>> Mac OS 에서는 NFD(Normalization Form Canonical Decomposition) 방식  

>> Windows 에서는 NFC(Normalization Form Canonical Composition) 방식을 사용합

참고 : <http://aero2blog.blogspot.kr/2011/07/macos-x.html>

## 문제 해결 스크립트
```perl
#!/usr/bin/env perl
# 사용법
# perl demacboogi.pl *.zip  #zip파일만 변환
# perl demacboogi.pl        #모든파일 변환
use 5.010;
use strict;
use warnings;
use Encode qw/encode decode/;
use Unicode::Normalize qw/compose/;
use File::Copy;

my @files = @ARGV;
@files = glob('*') if @files == 0;

foreach my $file (@files) {
    my $from = decode('utf8', $file);
    my $to = compose($from);
    if ($from ne $to) {
        say encode('utf8', "move $from -> $to");
        move($from, $to);
    }
}
```