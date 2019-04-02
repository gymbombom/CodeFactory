package cs;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

public class SoundSearcher {
	private static final char HANGUL_BEGIN_UNICODE = 44032; // 가 
	private static final char HANGUL_LAST_UNICODE = 55203; // // 힣 
	private static final char HANGUL_BASE_UNIT = 588;//각자음 마다 가지는 글자수
								
	private static final char[] INITIAL_SOUND = { 'ㄱ', 'ㄲ', 'ㄴ', 'ㄷ', 'ㄸ', 'ㄹ', 'ㅁ', 'ㅂ', 'ㅃ', 'ㅅ', 'ㅆ', 'ㅇ', 'ㅈ', 'ㅉ', 'ㅊ', 'ㅋ', 'ㅌ', 'ㅍ', 'ㅎ' }; 

	public SoundSearcher() { 
		
	} 

	private static boolean isInitialSound(char searchar){ 
		
		for(char c:INITIAL_SOUND){ 
			if(c == searchar){
				return true; 
			}
		}
		return false; 
	}
	
	private static char getInitialSound(char c) {
		int hanBegin = (c - HANGUL_BEGIN_UNICODE); int index = hanBegin / HANGUL_BASE_UNIT; 
		return INITIAL_SOUND[index]; 
		} 
	
	private static boolean isHangul(char c) { 
		
		return HANGUL_BEGIN_UNICODE <= c && c <= HANGUL_LAST_UNICODE; 
	} 

	
	public static boolean matchString(String value, String search){
		int t = 0; 
		int seof = value.length() - search.length(); 
		int slen = search.length();
		
		if(seof < 0) return false; //검색어가 더 길면 false를 리턴한다. 
		
		for(int i = 0;i <= seof;i++)
		{
			t = 0;
			while(t < slen) {
				if(isInitialSound(search.charAt(t))==true && isHangul(value.charAt(i+t)))
				{
					//만약 현재 char이 초성이고 value가 한글이면
					if(getInitialSound(value.charAt(i+t))==search.charAt(t))
					{
						t++;
					}
					else
					{
						break; 
					}

				}
				else
				{
					//char이 초성이 아니라면
					if(value.charAt(i+t)==search.charAt(t)) 
						t++;
					else
						break;
				}
				
				if(t == slen)
					return true; //모두 일치한 결과를 찾으면 true를 리턴한다.

			}
				

		}

		return false;
	}




	
	
	public static void main(String[] args)  {
		// TODO Auto-generated method stub
	boolean a = false;
	
	File file = new File("/Users/xxx/Desktop/aaa.txt");

	try {
		FileReader filereader = new FileReader(file);
		BufferedReader bufReader = new BufferedReader(filereader);
		String line = "";
		
		while((line = bufReader.readLine()) != null){
			a = matchString(line,"ㄱ ㅊㄹㅎ");
			if(a==true)
			{
				System.out.println(line);
			}
        }

		bufReader.close();
		
	} catch (Exception e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	
	
	}

}
