###############################################################################

### how to install git GUI(smart git 18.2.3) in your ubuntu 16.05
                                                commented by kwakdonghwan


아래의 스크립트를 터비널에서 실행해주세요.<br />
단!!!! 제발 sudo apt-get git 하고 설치하세요!!!!! <br />

###############################################################################

wget https://www.syntevo.com/downloads/smartgit/smartgit-linux-18_2_3.tar.gz <br />
tar -xzvf smartgit-linux-18_2_3.tar.gz <br />
cd smartgit <br />
cd bin <br />
chmod +x smartgit.sh <br />
sh smartgit.sh <br />

###############################################################################

설치 프로그램이 실행되면,

1. Non-commercial use only 채크하기
2. wait a few second, do license agreement
3. check Use SmartGit as SSH client
>>> 계속 진행하고 설치가 완료되면
1. 이름과 이메일 주소 입력하기
2. 우리 프로젝트 URI는 "https://github.com/woong164/RobomasterAIChallenge.git"
3. github와 연동할 폴더 선택하기 (원드라이브마냥 그쪽 폴더에 연동됩니다)
4. 실행하고 아무 파일이 없다고 당황하지 않기
5. 오른쪽 위에 File Filter 오른쪽에 종이모양 아이콘들 다 클릭하면 파일들이 나옵니다.

###############################################################################
### simple use of smart git

1. git에서 파일을 다운받을 때는 왼쪽 위에 pull버튼을 클릭합니다. 
2. git에 파일을 업로드할 때는 push버튼을 클릭하는데, 그전에! commit버튼으로 commit를 해주고 push합니다!

###############################################################################
