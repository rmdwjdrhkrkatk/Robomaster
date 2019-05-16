#-*- coding: utf-8 -*-
import os
import re
##############################################################
def rename(string):
    if (string != 'jpg' and string != 'png' ):
        print("잘못된 타입을 입력하셨습니다. ")
        return -1
    current_path = os.getcwd()  #현재 폴더 접근
    working_path = current_path + "\\img\\" #이미지 저장소 접근
    files = os.listdir(working_path)  #작업 이미지 폴더 확인
    try:

        files.sort(key=lambda var:[int(x) if x.isdigit() else x for x in re.findall(r'[^0-9]|[0-9]+', var)])
        print("숫자를 기반으로 재정의를 시작합니다.")

    except:
        print("다음과 같은경우 분류를 할 수 없습니다.")
        print("1.'순수문자.jpg'로 만 이루어져 있을 경우 ex)hhea.jpg")
        print("2.'문자+숫자.jpg'와 '순수 숫자.jpg'로 이루어져있을 경우 ex) 한글23.jpg + 332.jpg")
        print("프로그램 강제 종료")
        return -1

    number_of_files=len(files) # 작업할 이미지 숫자 확인
    print("작업 파일경로:" + working_path)
    print( "총 파일 갯수" + str(number_of_files) )
    start_number = int(input("시작하고 싶은 숫자를 입력해주세요:"))
    i=0

    while( i < number_of_files ): #각각의 데이터를 확인함.
        try:
            target_img = working_path + files[i]
            result_img = working_path + str(start_number) + "." + string
            os.rename(target_img,result_img)
            start_number = start_number+1
            i = i+1
        except:
            print("오류발생!")
            break
    print('rename 완료')
    return 0
##########################################################
#main fuction
#########################################################
print("이미지 이름 정렬기 1.01_곽동환")
print("이 정렬기는 다음과 같은 경우에 사용할 수 있습니다")
print("1. '순수숫자.jpg' 파일로만 이루어 져있을경우 ex)52.jpg , 2.jpg")
print("2. '순수숫자+문자.jpg' 파일로만 이루어져있을경우 ex)tehan_12.jpg , 한글_22.jpg")
string = input('변환할 이미지의 데이터 타입을 입력하세요.(jpg,png):')

rename(string)

###################################################
