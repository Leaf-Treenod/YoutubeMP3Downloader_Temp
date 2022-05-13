// Main.cpp
#include <iostream> 
#include <Windows.h> // ShellExecute() �Լ� ���� ���
#include <string>
#include <direct.h>	 // ���� ��θ� �ٲٴ� �Լ��� �����ϴ� ���
#include <io.h>		 // ���� ����� �Լ� ���� ���

#pragma warning(disable:4996) // _s ����� �ǰ��ϴ� ���� ����� �����ϰ� ��


// AutoHotKey ��ũ�θ� �ܺο��� ������ �� �ֵ��� ȣ���ϴ� �Լ� (cmdâ�� ctrl+v ����� ������ �Ѵ�)
void Call_AutoHotKey();
// AutoHotKey ��ũ�θ� �ܺο��� ����ɼ� �ֵ��� �ϴ� �Լ�
void Exit_AutoHotKey();
// ffmpeg�� �ִ� ������ ���� ��θ� �Ű��ִ� �Լ�
void ChangeDirectoryToffmpeg();
// Url�ּҸ� �Է¹޴� �Լ�
std::string InputUrl();
// YouTube�κ��� ���� ������ �ٿ�ε� �޴� �Լ�
void YouTubeMP3FileDownLoad(std::string url);
// ���� ���� track.flac�� ã���ִ� �Լ�
void FindFileNamedTrack();
// FLAC�� M4A�� ��ȯ���ִ� �Լ�
void ChangeFlacToM4A();
// File�̸��� ����ڰ� �Է��Ͽ� �ٲ��ִ� �Լ�
std::string RenameFile();
// ���� FLAC ������ �����ϰ� ���� ������ ������ ������ �̵����ִ� �Լ�
void RemoveAndMove(std::string fileName);




int main(void)
{

	// AutoHotKey ��ũ�θ� �ܺο��� ������ �� �ֵ��� ȣ���ϴ� �Լ� (cmdâ�� ctrl+v ����� ������ �Ѵ�)
	Call_AutoHotKey();
	// ffmpeg�� �ִ� ������ ���� ��θ� �Ű��ִ� �Լ�
	ChangeDirectoryToffmpeg(); 
	// YouTube�κ��� ���� ������ �ٿ�ε� �޴� �Լ�	 / ���������� ���� ������ URL�ּҸ� �޴� �Լ�
	YouTubeMP3FileDownLoad(InputUrl());
	//// ���� ���� track.flac�� ã���ִ� �Լ� (������ ������� �ʾƵ� �Ǵ� �Լ�)
	//// FindFileNamedTrack();	
	// FLAC�� M4A�� ��ȯ���ִ� �Լ�
	//ChangeFlacToM4A();	 
	// M4A���� ������ ������ ������ �̵����ִ� �Լ�	/ File�̸��� ����ڰ� �Է��Ͽ� �ٲ��ִ� �Լ�
	RemoveAndMove(RenameFile());
	// AutoHotKey ��ũ�θ� �ܺο��� ����ɼ� �ֵ��� �ϴ� �Լ�
	Exit_AutoHotKey();


	return 0;
}

// AutoHotKey ��ũ�θ� �ܺο��� ������ �� �ֵ��� ȣ���ϴ� �Լ� (cmdâ�� ctrl+v ����� ������ �Ѵ�)
void Call_AutoHotKey() {

	std::string fileName = "F://AutoHotkey//AutoHotKeyFiles//CtrlVmecro.exe";

	ShellExecute(NULL, "open", fileName.c_str(), NULL, NULL, SW_SHOW);
	printf("[AutoHotKey ��ũ�� ������ �����մϴ� CMDâ���� CTRL + V ����� ����Ͻ� �� �ֽ��ϴ�] \n");

}

// AutoHotKey ��ũ�θ� �ܺο��� ����ɼ� �ֵ��� �ϴ� �Լ�
void Exit_AutoHotKey() {

	FILE* file;		  // ���â(cmd)�� ���� �ݴµ� ���Ǵ� ���� ����
	char command[300] = "TASKKILL/im CtrlVmecro.exe";	// AutoHotKey ��׶��� ���μ����� �����ϴ� �ٽ� ��ɾ�
	char line[10240]; // ���â���� ��µǴ� �������� ����ִ� ����
	
	file = _popen(command, "r"); // command ������ ���� ��ɾ �����ϴ� cmdâ�� ����


	while(fgets(line, sizeof(line), file) != NULL) { // cmd�� ��µǴ� ������ line�� ��´� 
	
		printf("%s", line);	// cmd â�� line�� ���� ������ ����Ѵ�

	}
	//printf("[AutoHotKey ����] AutoHotKey ��׶��� ���μ����� �����Ͽ����ϴ� \n\n");

	fclose(file);


}


// ffmpeg�� �ִ� ������ ���� ��θ� �Ű��ִ� �Լ�
void ChangeDirectoryToffmpeg() {

	char cwd[1024];				// ���� ��θ� ��� ����
    _getcwd(cwd, sizeof(cwd));	// ���� ��θ� ȹ���ϴµ� �����ϸ� 0, �����ϸ� -1�� ��ȯ�Ѵ�
    printf("���� ���� ��� : %s\n",cwd);			// ���� ���� ��θ� ����Ѵ�


    if(_chdir("C:/Program Files/ffmpeg/bin") == 0) { // ���� ���ϰ�θ� �ٲٴµ� �����ϸ� 0�� ��ȯ�Ѵ� : _chdir()�Լ�
		printf("\"Change Directory Success\" \n");   // C:/Program Files/ffmpeg/bin �� ���� ���� ��ο���
	}												 //  \ ��� / �� ����ؾ� ������ ���� �ʴ´�
	else {
		printf("Change Directory Failed \n");		 // ���� ��� ���濡 �����ϸ� ���� ������ ����Ѵ�
	}

    _getcwd(cwd, sizeof(cwd));						 
    printf("������ ���� ��� : %s\n",cwd);			 // ���� ��� ���� ���Ŀ� ���� ��θ� ����Ѵ�
	printf("\n");
}

// Url�ּҸ� �Է¹޴� �Լ�
std::string InputUrl() {


	std::string temp;


	printf("���������� ���Ͻô� ������ url �ּҸ� �Է��Ͽ� �ֽʽÿ� : ");
	std::cin >> temp;
	std::cin.ignore();



	return temp;
}

// YouTube�κ��� ���� ������ �ٿ�ε� �޴� �Լ�
void YouTubeMP3FileDownLoad(std::string url) {

	FILE* file;		  // ���â(cmd)�� ���� �ݴµ� ���Ǵ� ���� ����
	char command[300] = "yt-dlp -x --audio-format mp3 --audio-quality 0 ";	// ���â���� ���� ��ɾ ��� ���� ��Ʃ�� ������ ���� ���Ϸ� �ٲ��ִ� �ٽ� ��ɾ�
	char line[10240]; // ���â���� ��µǴ� �������� ����ִ� ����
	char command2[30] = " -o\"track.%(mp3)s\"";
	

	strcat(command, "\"");
	strcat(command, url.c_str());	// ���� ��ɾ ��Ʃ�� ���� �ּҸ� �־��ش�
	strcat(command, "\"");
	strcat(command, command2);

	
	file = _popen(command, "r"); // command ������ ���� ��ɾ �����ϴ� cmdâ�� ����

	printf("[�ٿ�ε� ����] ���� ������ ���� ���Դϴ� ��ø� ��ٷ��ֽʽÿ� \n");	
	while(fgets(line, sizeof(line), file) != NULL) { // cmd�� ��µǴ� ������ line�� ��´� 
	
		printf("%s", line);	// cmd â�� line�� ���� ������ ����Ѵ�
	
	}
	printf("\n");
	printf("�ٿ�ε� ������ ��¹����� ��� ����Ͽ����ϴ� \n\n"); // while���� ���������� ���̻� ����� �������� �����Ƿ� ��� ������ ������ ����ڿ��� �˷��ش�
	fclose(file);


	printf("[�ٿ�ε� �Ϸ�] ���������� �Ϸ��Ͽ����ϴ� \n");

	//strstr()�Լ�

}

// ���� ���� track.flac�� ã���ִ� �Լ�
void FindFileNamedTrack() {

	// ���������� ã���ִ� ���
	std::string path = "C:/Program Files/ffmpeg/bin/*.flac";
	
	
	struct _finddata_t fd;
	
	intptr_t handle;
	
	if((handle = _findfirst(path.c_str(), &fd)) == -1L)	
		std::cout << "No file in directory!" << std::endl;
	
	do {
		printf("flac������ ���� ������ �߰��Ͽ����ϴ� \n");
		std::cout <<"���� ���ϸ� : "<< fd.name << std::endl;
	} while (_findnext(handle, &fd) == 0);
	printf("\n");

	_findclose(handle);	



}

// FLAC�� M4A�� ��ȯ���ִ� �Լ�
void ChangeFlacToM4A() {

	FILE* file;		  // ���â(cmd)�� ���� �ݴµ� ���Ǵ� ���� ����
	char command[300] = "ffmpeg -i track.flac -acodec alac track.m4a";	// FLAC���� ������ M4A�� ��ȯ���ִ� �ٽ� ��ɾ�
	char line[10240]; // ���â���� ��µǴ� �������� ����ִ� ����
	

	//freopen("output.txt", "w", stdout);

	file = _popen(command, "r"); // command ������ ���� ��ɾ �����ϴ� cmdâ�� ����

	printf("[���� ��ȯ ����]FLAC������ ������ M4A�� ��ȯ�մϴ� \n");
	printf("������ ��ȯ���Դϴ� ��ø� ��ٷ��ֽʽÿ� \n");
	while(fgets(line, sizeof(line), file) != NULL) { // cmd�� ��µǴ� ������ line�� ��´� 
		
			printf("%s", line);	// cmd â�� line�� ���� ������ ����Ѵ�

	}
	printf("[���� ��ȯ �Ϸ�] M4A�� ���� ��ȯ�� �Ϸ��Ͽ����ϴ� \n\n");

	fclose(file);
	
}

// File�̸��� ����ڰ� �Է��Ͽ� �ٲ��ִ� �Լ�
std::string RenameFile() {

	std::string newName;
	
	printf("������� ���� ���Ͽ� ���ο� �̸��� �Է��Ͽ� �ֽʽÿ� : ");
	std::getline(std::cin, newName);


	
	newName += ".mp3";
	rename("track.mp3", newName.c_str());

	printf("�̸� ������ �Ϸ�Ǿ����ϴ� \n");

	return newName;
}

// ���� FLAC ������ �����ϰ� ���� ������ ������ ������ �̵����ִ� �Լ�
void RemoveAndMove(std::string fileName) {
	

	setlocale(LC_ALL, "Korean");	// �ѱ۷� �̷���� ���� �ּҸ� �������� ���ȴ�
	

	std::string address		= "F:/Music/ī�� ���� ���� MP3/";		// �̵��ϰ� �� ��� �ּ�
	std::string oldAddress	= "C:/Program Files/ffmpeg/bin/";	// �̵��ϱ� ���� �ּ�
	int e = -1;						// ���� ������ �̵��� ���� �Լ� ��ȯ���� ��� ����



	address += fileName;		// �̵��ϰ� �� ��� �ּҿ� ���� �̸��� �ٿ��ش�
	//e = remove("track.flac");	// ������ �����ϴ� track.flac ���� ������ �����Ѵ� e�� ��ȯ�� ����

	// e�� 0�� ��ȯ������ ���� ���� ���� �� �ܿ��� ����
	//if(e == 0)
	//	printf("[Success Remove] ���� FLAC ���� ���� ���� \n");
	//else
	//	printf("[Error Remove] ���� FLAC ���� ���� �Ұ� \n");


	printf("[���� ��� ������]������ ��θ� �̵����Դϴ� â�� ���� �����ּ��� \n");
	//e = -1;	// e���� �ٸ� �Լ��κ��� ��ȯ �ޱ� ���� �ٽ� �ʱ�ȭ
	e =	rename((oldAddress + fileName).c_str(), address.c_str());	// ���� ��� �ű��
	
	// e�� 0�� ��ȯ������ ���� ��� �̵� ���� �� �ܿ��� ����
	if(e == 0)
		printf("[Success Rename] ���ϰ�� �̵� ���� \n");
	else
		printf("[Error Rename] ���ϰ�� �̵� ���� \n");

	
	printf("[ALL COMPLETE]��� �۾��� ���ƽ��ϴ� �̿����ּż� �����մϴ� \n\n");

}