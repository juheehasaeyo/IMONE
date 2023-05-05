#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 파싱 데이터 저장 구조체
typedef struct
{
    int AcX;
    int AcY;
    int AcZ;
    float Tmp;
    int GyX;
    int GyY;
    int GyZ;
} MPU6050Data;

void parseMPU6050Data(char *str, MPU6050Data *data)
{
    char *token;
    char *delim = " =|";
    char *keywords[] = {"AcX", "AcY", "AcZ", "Tmp", "GyX", "GyY", "GyZ"};
    token = strtok(str, delim);
    while (token != NULL)
    {
        // 파싱된 문자열이 키워드에 해당하는지 확인하여 값을 저장
        for (int i = 0; i < 7; i++)
        {
            if (strcmp(token, keywords[i]) == 0)
            {
                token = strtok(NULL, delim);
                switch (i)
                {
                case 0: // AcX
                    data->AcX = atoi(token);
                    break;
                case 1: // AcY
                    data->AcY = atoi(token);
                    break;
                case 2: // AcZ
                    data->AcZ = atoi(token);
                    break;
                case 3: // Tmp
                    data->Tmp = atof(token);
                    break;
                case 4: // GyX
                    data->GyX = atoi(token);
                    break;
                case 5: // GyY
                    data->GyY = atoi(token);
                    break;
                case 6: // GyZ
                    data->GyZ = atoi(token);
                    break;
                }
                break;
            }
        }
        token = strtok(NULL, delim);
    }
}

int main()
{

    printf("센서 데이터: ");
    char sensordata[80];
    fgets(sensordata, 200, stdin);
    // gets(sensordata);
    //  입력 문자열 파싱하여 구조체에 저장
    MPU6050Data data;
    parseMPU6050Data(sensordata, &data);

    // 구조체에 저장된 값 출력
    printf("X축 가속도 = %d\n", data.AcX);
    printf("Y축 가속도 = %d\n", data.AcY);
    printf("Z축 가속도 = %d\n", data.AcZ);
    printf("온도 = %f\n", data.Tmp);
    printf("X축 자이로스코프 기울기 = %d\n", data.GyX);
    printf("Y축 자이로스코프 기울기 = %d\n", data.GyY);
    printf("Z축 자이로스코프 기울기 = %d\n", data.GyZ);
}
