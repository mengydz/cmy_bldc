/*==================================================================================================== 
						����ʽPID
The PID (���������֡�΢��) function is used in mainly 
control applications. PIDCalc performs one iteration of the PID 
algorithm. 
While the PID function works, main is just a dummy program showing 
a typical usage. 
=====================================================================================================*/
#define Set_Point	1000	 //100 10000
#define PWM_Max		1400
#define PWM_Min     50  
typedef struct PID 
{ 
	int Target;     //�趨Ŀ�� Desired Value
	int Uk;			//Uk
	int Udk;		//Udk����
	int Uk_1; 		//Uk-1
	double P; 		//�������� Proportional Const 
	double I; 		//���ֳ��� Integral Const
	int    b; 
	double D; 		//΢�ֳ��� Derivative Const
	int ek_0;		//ek 
	int ek_1; 		//ek-1 
	int ek_2; 		//ek-2 
}PID;
static PID Speed_PID; 
static PID *Speed_Point = &Speed_PID; 
/*==================================================================================================== 
Initialize PID Structure PID������ʼ��
=====================================================================================================*/ 
void Speed_PIDInit(void) 
{ 
	Speed_Point->Target = Set_Point;
	Speed_Point->Uk		= 0;
	Speed_Point->Udk    = 0;
	Speed_Point->Uk_1   = PWM_Min;
	Speed_Point->ek_0 	= 0;	 //ek=0
	Speed_Point->ek_1 	= 0;	 //ek-1=0
	Speed_Point->ek_2 	= 0; 	 //ek-2=0
	Speed_Point->P 		= 4;  //�������� Proportional Const 
	Speed_Point->I 		= 0.084; 	 //���ֳ���Integral Const
	Speed_Point->b      = 1; 
	Speed_Point->D 		= 1.8; 	 //΢�ֳ��� Derivative Const 
}
/*==================================================================================================== 
����ʽPID���㲿�� 
=====================================================================================================*/ 
int Speed_PIDAdjust(int Next_Point) 
{ 
	Speed_Point->ek_0= Speed_Point->Target - Next_Point; 	//��������
	/*�����������ּ�������Uk���뱥��������ֹͣ��������Ļ��������㣬��ֻ����ʹ���ּ��ٵ�����*/
	if(((Speed_Point->Uk_1>=PWM_Max)&&(Speed_Point->ek_0>=0))||((Speed_Point->Uk_1<=PWM_Min)&&(Speed_Point->ek_0<=0)))
	{
	    Speed_Point->b=0;
	} 
	else
	{
		Speed_Point->b=1;
	} 
	Speed_Point->Udk=Speed_Point->P*(Speed_Point->ek_0-Speed_Point->ek_1) + Speed_Point->b*Speed_Point->I*Speed_Point->ek_0 
		+ Speed_Point->D*(Speed_Point->ek_0-2*Speed_Point->ek_1+Speed_Point->ek_2);
    /* �洢�������´μ��� */
	Speed_Point->Uk = Speed_Point->Uk_1 + Speed_Point->Udk;

	Speed_Point->ek_2 =	Speed_Point->ek_1;
	Speed_Point->ek_1 = Speed_Point->ek_0;
	Speed_Point->Uk_1 = Speed_Point->Uk; 
    if(Speed_Point->Uk >= PWM_Max)
	{
		return PWM_Max;
	}
	else if(Speed_Point->Uk <= PWM_Min)
	{
		return PWM_Min;
	} 
	return(Speed_Point->Uk); 
}
