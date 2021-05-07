#include <stdio.h>
#include "vad/webrtc_vad.h"
#include <math.h>
#include"voice_qa.h"
#define FRAMESIZE 160
int main(int argc, char** argv)
{
	FILE* fpInput, * fpOutput, * fpOut;
	VadInst* vadInst;
	vadInst = NULL;
	short* f_buf; short* fout_buf;
	int s_frame = 0, n_frame = 0, snr_frame = 0;
	float Vox_qa = 0.0;
	int fs = 16000;
	int vad_mode = 1;
	int status = 0;
	float snr;
	short audioFrame[FRAMESIZE];
	double s = 0.0, n = 0.0, s_tmp = 0.0;  
	//f_buf = new short[FRAMESIZE];
	//fout_buf = new short[FRAMESIZE];
	fpInput = fopen("./0010.wav", "rb");


	if (fpInput == NULL)
	{
		printf("open file failure\n");
		return -1;
	}
	fpOutput = fopen("./test1.txt", "wb");
	if (fpOutput == NULL)
	{
		printf("open file failure\n");
		return -1;
	}
	status = WebRtcVad_Create(&vadInst);
	if (status == NULL)
	{
		printf("Create is error \n");

	}
	status = WebRtcVad_Init(vadInst);//创建模型
	if (status != 0)
	{
		printf("WebRtcVad Init is error\n");
		WebRtcVad_Free(vadInst);
		return -1;
	}

	status = WebRtcVad_set_mode(vadInst, 1);//设置模型参数
	if (status != 0)
	{
		printf("WebRtcVad set mode is error\n");

		return -1;
	}
	printf("Activity : \n");
	while (!feof(fpInput))
	{
		fread(audioFrame, sizeof(short), FRAMESIZE, fpInput);
		status = WebRtcVad_Process(vadInst, fs, audioFrame, FRAMESIZE);
		if (status == -1)
		{
			printf("WebRtcVad_Process is error\n");
			WebRtcVad_Free(vadInst);
			return -1;
		}
		else if (status == 1)
		{
			printf("Active Voice\n");
			for (int i = 0; i < FRAMESIZE; i++)
			{
				s += (float)audioFrame[i] * audioFrame[i];
			}
			s_frame++;
			if (s_frame > 5)//截取前5帧作为估计的噪声
			{
				s_tmp = s;
			}
		}
		else
		{
			printf("Non-active Voice\n");
			for (int i = 0; i < FRAMESIZE; i++)
			{
				n += (float)audioFrame[i] * audioFrame[i];
			}
			n_frame++;
			

		}
		snr_frame++;


		fprintf(fpOutput, "%2d", status);
	}
	//printf("snr_frame  is  %d\n", snr_frame);
	//printf("s_frame  is  %d\n", s_frame);
	//printf("n_frame  is  %d\n", n_frame);
	//对于噪声很大的情况下，可以截取一段开始的语音作为噪声
		if ((snr_frame - s_frame) < 10)
		{
			//截取开始的一段语音(10帧)作为噪声
			
				n = s_tmp;
				
				n_frame = 5;

		}
			printf("n_frame  is  %d\n", n_frame);
	float s1= s / s_frame;
	
	float n1= n / n_frame;

	printf("n1  is  %f\n", n1);
	//float sn = 10 * log10(s1 / n1) - 1;
	snr = 10 * log10((s / s_frame) / (n / n_frame)) - 1;
	fprintf(stderr, "SNR = %f \n", snr);
	//根据信噪比来计算语音质量，如果snr超过100或者其他数字，显示
	int sa = voice_qa(snr);
printf("sa si %d \n", sa);
	fclose(fpInput);
	fclose(fpOutput);
	WebRtcVad_Free(vadInst);

	 printf("pree any key to exit.\n");
	printf("Finished \n");
	getchar();
	return 0;
}  
