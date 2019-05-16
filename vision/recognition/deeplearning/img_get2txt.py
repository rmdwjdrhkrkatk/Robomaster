#-*- coding: utf-8 -*-
import os
import csv
import re
####################################################파일경로 설정 및 csv형식 호출###########
current_path = os.getcwd()  #현재 폴더 접근
working_path = current_path + "\\img\\" #이미지 저장소 접근
file =  open(working_path + 'img_gt.txt' , 'r' , encoding='utf-8' )  #csv 파일 오픈
read_line = csv.reader(file)  #csv파일 읽기
####################################################데이터 접근 및 연산 함수################
def calculate(x,y,width,hight,Total_width = 640, Total_hight =480):  #기본값으로 640X480을 받음
    x = int(x)
    y = int(y)
    if (x==0 or y==0):
        return -1
    width = int(width)
    hight = int(hight)
    x = x / Total_width
    y = y / Total_hight
    width = width / Total_width
    hight = hight / Total_hight
    x = x + width/2
    y = y + hight/2

    if (((x+width*0.5)>=1) or ((y+hight*0.5)>=1)):
        if (x+width*0.5)>=1 :
            width = (1-(x-width*0.5))-0.01
            result = [x, y, width, hight]
            return result
        elif (y+hight*0.5)>=1 :
            hight = (1-(y-hight*0.5))-0.01
            result = [x, y, width, hight]
            return result


    result = [x, y, width, hight]

    return result
####################################################주 작업 시작 ###########################
for line in read_line:  #한줄씩 데이터 처리. (iterable한 타입이므로 다음과 같이 불어올 수 있음.
    classnumber = int(line[1])
    for i in range (1,classnumber+1):
        Spstring=str(line[0]).split('.')       # jpg to txt
        txtform = Spstring[0] + '.txt'
        txtfilename = working_path + txtform   # txt경로 지정
        TXTfile = open(txtfilename,'a', encoding='utf-8')   #txt 오픈 함수
        result=calculate(line[5*i-3],line[5*i-2],line[5*i-1],line[5*i])
        if result == -1:
            print(line[0]+ "가 이상합니다.")
        try:
            result[0] = str(result[0])
            result[1] = str(result[1])
            result[2] = str(result[2])
            result[3] = str(result[3])
        except:
            continue

        if classnumber==1 :
            TXTfile.write(line[6] + " " + result[0] + ' ' + result[1] + ' ' + result[2] + ' ' + result[3])

        elif classnumber==2 and i==1 :
            TXTfile.write(line[6] + " " + result[0] + ' ' + result[1] + ' ' + result[2] + ' ' + result[3])
        elif classnumber==2 and i==2 :
            TXTfile.write("\n" + line[11] + " " + result[0] + ' ' + result[1] + ' ' + result[2] + ' ' + result[3])

            #if result != -1 and line[6]==1 :
            #   TXTfile.write("1" + result[0] + ' ' + result[1] + ' ' + result[2] + ' ' + result[3])  ## if i == classnumber final = ''

            #elif result != -1 and line[11]==1 :
            #    TXTfile.write("1" + result[0] + ' ' + result[1] + ' ' + result[2] + ' ' + result[3])
        #elif classnumber==2 and i==2 :
            #if result != -1 and line[6]==2 :
            #    TXTfile.write("\n" + "2" + result[0] + ' ' + result[1] + ' ' + result[2] + ' ' + result[3])

            #elif result != -1 and line[11]==2 :
            #    TXTfile.write("\n" + "2" + result[0] + ' ' + result[1] + ' ' + result[2] + ' ' + result[3])



        #elif result == -1:
         #   print("오류가 있습니다."+txtform)

    TXTfile.close()                #txt에 쓰기


file.close()  #csv파일 종료
