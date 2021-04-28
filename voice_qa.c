#include<stdio.h>
#include<math.h>
int voice_qa(const float number)
{
	float s_tmp;
	int Qa_voice = 0;
	printf("the number is %f \n", number);
	s_tmp = number;
	printf("the s_tmp number is %f \n", s_tmp);
	if (number < 0.0)
	{
		printf("the voice quality is wrong \n");
		return -1;
	}
	else if (0.0< number < 1000.0)
	{

		s_tmp = s_tmp * 8.0 - 0.5;
		Qa_voice = ceil(s_tmp);
	}
	else
	{
		printf("pelease check you voice  \n");
		return 0;
	}
	return Qa_voice;
}