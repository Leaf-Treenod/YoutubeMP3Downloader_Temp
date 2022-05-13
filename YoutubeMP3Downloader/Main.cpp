// Main.cpp
#include <iostream> 
#include <Windows.h> // ShellExecute() 함수 포함 헤더
#include <string>
#include <direct.h>	 // 파일 경로를 바꾸는 함수를 포함하는 헤더
#include <io.h>		 // 파일 입출력 함수 포함 헤더

#pragma warning(disable:4996) // _s 사용을 권고하는 문구 출력을 무시하게 함


// AutoHotKey 매크로를 외부에서 실행할 수 있도록 호출하는 함수 (cmd창에 ctrl+v 기능을 가능케 한다)
void Call_AutoHotKey();
// AutoHotKey 매크로를 외부에서 종료될수 있도록 하는 함수
void Exit_AutoHotKey();
// ffmpeg이 있는 곳으로 파일 경로를 옮겨주는 함수
void ChangeDirectoryToffmpeg();
// Url주소를 입력받는 함수
std::string InputUrl();
// YouTube로부터 음원 파일을 다운로드 받는 함수
void YouTubeMP3FileDownLoad(std::string url);
// 음원 파일 track.flac을 찾아주는 함수
void FindFileNamedTrack();
// FLAC을 M4A로 변환해주는 함수
void ChangeFlacToM4A();
// File이름을 사용자가 입력하여 바꿔주는 함수
std::string RenameFile();
// 기존 FLAC 파일을 삭제하고 음원 파일을 지정한 곳으로 이동해주는 함수
void RemoveAndMove(std::string fileName);




int main(void)
{

	// AutoHotKey 매크로를 외부에서 실행할 수 있도록 호출하는 함수 (cmd창에 ctrl+v 기능을 가능케 한다)
	Call_AutoHotKey();
	// ffmpeg이 있는 곳으로 파일 경로를 옮겨주는 함수
	ChangeDirectoryToffmpeg(); 
	// YouTube로부터 음원 파일을 다운로드 받는 함수	 / 음원추출을 위한 영상의 URL주소를 받는 함수
	YouTubeMP3FileDownLoad(InputUrl());
	//// 음원 파일 track.flac을 찾아주는 함수 (이제는 사용하지 않아도 되는 함수)
	//// FindFileNamedTrack();	
	// FLAC을 M4A로 변환해주는 함수
	//ChangeFlacToM4A();	 
	// M4A음원 파일을 지정한 곳으로 이동해주는 함수	/ File이름을 사용자가 입력하여 바꿔주는 함수
	RemoveAndMove(RenameFile());
	// AutoHotKey 매크로를 외부에서 종료될수 있도록 하는 함수
	Exit_AutoHotKey();


	return 0;
}

// AutoHotKey 매크로를 외부에서 실행할 수 있도록 호출하는 함수 (cmd창에 ctrl+v 기능을 가능케 한다)
void Call_AutoHotKey() {

	std::string fileName = "F://AutoHotkey//AutoHotKeyFiles//CtrlVmecro.exe";

	ShellExecute(NULL, "open", fileName.c_str(), NULL, NULL, SW_SHOW);
	printf("[AutoHotKey 매크로 실행을 시작합니다 CMD창에서 CTRL + V 기능을 사용하실 수 있습니다] \n");

}

// AutoHotKey 매크로를 외부에서 종료될수 있도록 하는 함수
void Exit_AutoHotKey() {

	FILE* file;		  // 명령창(cmd)을 열고 닫는데 사용되는 파일 변수
	char command[300] = "TASKKILL/im CtrlVmecro.exe";	// AutoHotKey 백그라운드 프로세스를 종료하는 핵심 명령어
	char line[10240]; // 명령창에서 출력되는 구문들을 담아주는 변수
	
	file = _popen(command, "r"); // command 변수에 담은 명령어를 실행하는 cmd창을 연다


	while(fgets(line, sizeof(line), file) != NULL) { // cmd에 출력되는 구문을 line에 담는다 
	
		printf("%s", line);	// cmd 창에 line에 담은 구문을 출력한다

	}
	//printf("[AutoHotKey 종료] AutoHotKey 백그라운드 프로세스를 종료하였습니다 \n\n");

	fclose(file);


}


// ffmpeg이 있는 곳으로 파일 경로를 옮겨주는 함수
void ChangeDirectoryToffmpeg() {

	char cwd[1024];				// 파일 경로를 담는 변수
    _getcwd(cwd, sizeof(cwd));	// 파일 경로를 획득하는데 성공하면 0, 실패하면 -1을 반환한다
    printf("현재 파일 경로 : %s\n",cwd);			// 현재 파일 경로를 출력한다


    if(_chdir("C:/Program Files/ffmpeg/bin") == 0) { // 만일 파일경로를 바꾸는데 성공하면 0을 반환한다 : _chdir()함수
		printf("\"Change Directory Success\" \n");   // C:/Program Files/ffmpeg/bin 과 같이 파일 경로에서
	}												 //  \ 대신 / 을 사용해야 오류가 나지 않는다
	else {
		printf("Change Directory Failed \n");		 // 파일 경로 변경에 실패하면 오류 구문을 출력한다
	}

    _getcwd(cwd, sizeof(cwd));						 
    printf("수정된 파일 경로 : %s\n",cwd);			 // 파일 경로 변경 이후에 현재 경로를 출력한다
	printf("\n");
}

// Url주소를 입력받는 함수
std::string InputUrl() {


	std::string temp;


	printf("음원추출을 원하시는 영상의 url 주소를 입력하여 주십시오 : ");
	std::cin >> temp;
	std::cin.ignore();



	return temp;
}

// YouTube로부터 음원 파일을 다운로드 받는 함수
void YouTubeMP3FileDownLoad(std::string url) {

	FILE* file;		  // 명령창(cmd)을 열고 닫는데 사용되는 파일 변수
	char command[300] = "yt-dlp -x --audio-format mp3 --audio-quality 0 ";	// 명령창에서 쓰일 명령어를 담는 변수 유튜브 영상을 음원 파일로 바꿔주는 핵심 명령어
	char line[10240]; // 명령창에서 출력되는 구문들을 담아주는 변수
	char command2[30] = " -o\"track.%(mp3)s\"";
	

	strcat(command, "\"");
	strcat(command, url.c_str());	// 메인 명령어에 유튜브 영상 주소를 넣어준다
	strcat(command, "\"");
	strcat(command, command2);

	
	file = _popen(command, "r"); // command 변수에 담은 명령어를 실행하는 cmd창을 연다

	printf("[다운로드 시작] 음원 파일을 추출 중입니다 잠시만 기다려주십시오 \n");	
	while(fgets(line, sizeof(line), file) != NULL) { // cmd에 출력되는 구문을 line에 담는다 
	
		printf("%s", line);	// cmd 창에 line에 담은 구문을 출력한다
	
	}
	printf("\n");
	printf("다운로드 과정의 출력문들을 모두 출력하였습니다 \n\n"); // while문을 빠져나오면 더이상 출력할 구문들이 없으므로 출력 구문이 없음을 사용자에게 알려준다
	fclose(file);


	printf("[다운로드 완료] 음원추출을 완료하였습니다 \n");

	//strstr()함수

}

// 음원 파일 track.flac을 찾아주는 함수
void FindFileNamedTrack() {

	// 음원파일을 찾아주는 기능
	std::string path = "C:/Program Files/ffmpeg/bin/*.flac";
	
	
	struct _finddata_t fd;
	
	intptr_t handle;
	
	if((handle = _findfirst(path.c_str(), &fd)) == -1L)	
		std::cout << "No file in directory!" << std::endl;
	
	do {
		printf("flac형식의 음원 파일을 발견하였습니다 \n");
		std::cout <<"음원 파일명 : "<< fd.name << std::endl;
	} while (_findnext(handle, &fd) == 0);
	printf("\n");

	_findclose(handle);	



}

// FLAC을 M4A로 변환해주는 함수
void ChangeFlacToM4A() {

	FILE* file;		  // 명령창(cmd)을 열고 닫는데 사용되는 파일 변수
	char command[300] = "ffmpeg -i track.flac -acodec alac track.m4a";	// FLAC음원 파일을 M4A로 변환해주는 핵심 명령어
	char line[10240]; // 명령창에서 출력되는 구문들을 담아주는 변수
	

	//freopen("output.txt", "w", stdout);

	file = _popen(command, "r"); // command 변수에 담은 명령어를 실행하는 cmd창을 연다

	printf("[파일 변환 시작]FLAC형식의 파일을 M4A로 변환합니다 \n");
	printf("파일을 변환중입니다 잠시만 기다려주십시오 \n");
	while(fgets(line, sizeof(line), file) != NULL) { // cmd에 출력되는 구문을 line에 담는다 
		
			printf("%s", line);	// cmd 창에 line에 담은 구문을 출력한다

	}
	printf("[파일 변환 완료] M4A로 파일 변환을 완료하였습니다 \n\n");

	fclose(file);
	
}

// File이름을 사용자가 입력하여 바꿔주는 함수
std::string RenameFile() {

	std::string newName;
	
	printf("만들어진 음원 파일에 새로운 이름을 입력하여 주십시오 : ");
	std::getline(std::cin, newName);


	
	newName += ".mp3";
	rename("track.mp3", newName.c_str());

	printf("이름 변경이 완료되었습니다 \n");

	return newName;
}

// 기존 FLAC 파일을 삭제하고 음원 파일을 지정한 곳으로 이동해주는 함수
void RemoveAndMove(std::string fileName) {
	

	setlocale(LC_ALL, "Korean");	// 한글로 이루어진 파일 주소를 읽을때에 사용된다
	

	std::string address		= "F:/Music/카페 음악 모음 MP3/";		// 이동하게 될 대상 주소
	std::string oldAddress	= "C:/Program Files/ffmpeg/bin/";	// 이동하기 이전 주소
	int e = -1;						// 파일 삭제와 이동에 관한 함수 반환값을 담는 변수



	address += fileName;		// 이동하게 될 대상 주소에 파일 이름을 붙여준다
	//e = remove("track.flac");	// 이전에 존재하던 track.flac 음원 파일은 삭제한다 e에 반환값 저장

	// e가 0을 반환받으면 파일 삭제 성공 그 외에는 실패
	//if(e == 0)
	//	printf("[Success Remove] 기존 FLAC 파일 삭제 성공 \n");
	//else
	//	printf("[Error Remove] 기존 FLAC 파일 삭제 불가 \n");


	printf("[파일 경로 변경중]파일의 경로를 이동중입니다 창을 닫지 말아주세요 \n");
	//e = -1;	// e값을 다른 함수로부터 반환 받기 전에 다시 초기화
	e =	rename((oldAddress + fileName).c_str(), address.c_str());	// 파일 경로 옮기기
	
	// e가 0을 반환받으면 파일 경로 이동 성공 그 외에는 실패
	if(e == 0)
		printf("[Success Rename] 파일경로 이동 성공 \n");
	else
		printf("[Error Rename] 파일경로 이동 실패 \n");

	
	printf("[ALL COMPLETE]모든 작업을 마쳤습니다 이용해주셔서 감사합니다 \n\n");

}