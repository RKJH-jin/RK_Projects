#pragma once
#include "gameNode.h"
#include <iostream> 
#include <fstream>
#include <string> //get라인함수를 위해서 필요함

using namespace std;
/*
ifstream : 파일 읽기
ofstream : 파일 쓰기 <<이건 안쓸걸 읽기만한다면..
*/

class csv : public gameNode
{
public:
	void read()
	{
		//파일 쓰는 부분 덮어씌워버림
		/*
		ofstream output("가구.csv"); //쓸파일의 이름과 확장자를 정함
		output << "Hello World!, 안뇽" << endl; //파일에 쓸 내용 입력
		output.close(); //파일닫기*/

		string str_buf; //읽은 문자를 받을 버퍼
		ifstream file; //파일읽는 자료형. 파일의 자료형

		file.open("objectFile.csv", ios::in);

		//fail()함수 : 파일 여는것에 실패할경우를 알려줌 
		if (file.fail())cout << "파일을 여는 데 실패했습니다." << endl;

		while (!file.eof()) //eof: 파일의 끝이아니면 계속 반복. 이파일 끝날때까지 계속 즉 끝까지 읽어라.
		{
			getline(file, str_buf, ','); //파일이담긴 변수 / 문자를 받을 버퍼 / 구분자
			DATAMANAGER->_vStr_buf.push_back(str_buf);
		}

		file.close();

	}
};

