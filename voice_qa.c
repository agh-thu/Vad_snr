#include<stdio.h>
#include<math.h>
int voice_qa(const float number)
{
	float s_tmp;
	int Qa_voice = 0;
	//printf("the number is %f \n", number);
	s_tmp = number;
	//printf("the s_tmp number is %f \n", s_tmp);
	if (number < 0.0)
	{
		printf("the voice quality too low \n");
		//量化 往下直接取整
		s_tmp = s_tmp - 0.5;
		Qa_voice = ceil(s_tmp);
		//Qa_voice = -1; //也可以直接赋值
	}
	else if (number < 1000.0)
	{

		s_tmp = s_tmp * 2.0 - 0.5;
		Qa_voice = ceil(s_tmp);
	
	}
	else
	{
		printf("pelease check you voice  \n");
		Qa_voice = 0;
	}
	return Qa_voice;
}