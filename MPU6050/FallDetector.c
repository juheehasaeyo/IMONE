    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    // 파싱 데이터 저장 구조체
    typedef struct {
        int AcX;
        int AcY;
        int AcZ;
        float Tmp;
        int GyX;
        int GyY;
        int GyZ;
    } MPU6050Data;


    void parseMPU6050Data(char *str, MPU6050Data *data) {
        char *token;
        char *delim = " =|";
        char *keywords[] = {"AcX", "AcY", "AcZ", "Tmp", "GyX", "GyY", "GyZ"};
        token = strtok(str, delim);
        while (token != NULL) {
            // 파싱된 문자열이 키워드에 해당하는지 확인하여 값을 저장
            for (int i = 0; i < 7; i++) {
                if (strcmp(token, keywords[i]) == 0) {
                    token = strtok(NULL, delim);
                    switch (i) {
                        case 0:  // AcX
                            data->AcX = atoi(token);
                            break;
                        case 1:  // AcY
                            data->AcY = atoi(token);
                            break;
                        case 2:  // AcZ
                            data->AcZ = atoi(token);
                            break;
                        case 3:  // Tmp
                            data->Tmp = atof(token);
                            break;
                        case 4:  // GyX
                            data->GyX = atoi(token);
                            break;
                        case 5:  // GyY
                            data->GyY = atoi(token);
                            break;
                        case 6:  // GyZ
                            data->GyZ = atoi(token);
                            break;
                    }
                    break;
                }
            }
            token = strtok(NULL, delim);
        }
    }

     //데이터 받아올 때마다 누적 데이터의 평균 값 뽑아내는 함수로 수정

    // X축 가속도값 임계값 초과 여부 판단 boolean 함수
    int isAcXOver(int AcX) {
        if(abs(AcX) > 88 && abs(AcX) < 444) {
            return 1;
        }
        return 0;
    }

    // Y축 가속도값 임계값 초과 여부 판단 boolean 함수
    int isAcYOver(int AcY) {
        if(abs(AcY) > 2336  && abs(AcY) < 2972) {
            return 1;
        }
        return 0;
    }

    // Z축 가속도값 임계값 초과 여부 판단 boolean 함수
    int isAcZOver(int AcZ) {
        if(abs(AcZ) > 18104 && abs(AcZ) < 18964) {
            return 1;
        }
        return 0;
    }

    // X축 각속도값 임계값 초과 여부 판단 boolean 함수
    int isGyXOver(int GyX) {
        if(abs(GyX) > 441 && abs(GyX) < 604) {
            return 1;
        }
        return 0;
    }

    // Y축 각속도값 임계값 초과 여부 판단 boolean 함수
    int isGyYOver(int GyY) {
        if(abs(GyY) > 304 && abs(GyY) < 461) {
            return 1;
        }
        return 0;
    }

    // Z축 각속도값 임계값 초과 여부 판단 boolean 함수
    int isGyZOver(int GyZ) {
        if(abs(GyZ) > 11 && abs(GyZ) < 77) {
            return 1;
        }
        return 0;
    }

    int FallDetector() {
        
        //누적 변수 선언
        int totAcX = 0;
        int totAcY = 0;
        int totAcZ = 0;
        int totGyX = 0;
        int totGyY = 0;
        int totGyZ = 0;
        int avgAcX = 0;
        int avgAcY = 0;
        int avgAcZ = 0;
        int avgGyX = 0;
        int avgGyY = 0;
        int avgGyZ = 0;
        int count = 0;
        int fallCount = 0;
        
        while (count != -1) {
            
            printf("센서 데이터: ");
            char sensordata[80];
            fgets(sensordata, 200, stdin);
            MPU6050Data data;
            parseMPU6050Data(sensordata, &data);
                
            //현재까지 데이터 받은 횟수 저장 변수
            count = count + 1;
                
            //값 누적부
            totAcX = totAcX + data.AcX;
            totAcY = totAcY + data.AcY;
            totAcZ = totAcZ + data.AcZ;
            totGyX = totGyX + data.GyX;
            totGyY = totGyY + data.GyY;
            totGyZ = totGyZ + data.GyZ;
            
            // 각 데이터 평균값 구하는 부분
            avgAcX = (int)totAcX / count;
            avgAcY = (int)totAcY / count;
            avgAcZ = (int)totAcZ / count;
            avgGyX = (int)totGyX / count;
            avgGyY = (int)totGyY / count;
            avgGyZ = (int)totGyZ / count;
            
            // 각 데이터가 모두 임계값을 초과할 시 낙상 판단 변수 fallCount를 1 증가
            if(isAcXOver(avgAcX) && isAcYOver(avgAcY) && isAcZOver(avgAcZ) && isGyXOver(avgGyX) && isGyYOver(avgGyY) && isGyZOver(avgGyZ)) {
                fallCount += 1;
            }
            
            
            // 데이터의 노이즈를 방지하기 위해 데이터를 5번 받아와서 그 중 3번 이상 낙상 데이터가 탐지되면 낙상사고가 발생하였다고 판단
            if (count % 5 == 0) {
                if (fallCount >= 3) {
                    printf("fall detected");
                    return 0;
                }
                // 각 변수값 재초기화
                totAcX = 0;
                totAcY = 0;
                totAcZ = 0;
                totGyX = 0;
                totGyY = 0;
                totGyZ = 0;
                avgAcX = 0;
                avgAcY = 0;
                avgAcZ = 0;
                avgGyX = 0;
                avgGyY = 0;
                avgGyZ = 0;
                fallCount = 0;
            }
        }
    }
