#include "XOR_Neural_Network.h"
#include "SaveLoad/SaveLoad.h"

int main()
{
	int choice;
    int err;
    char line[256], *p;
	char stop;
	struct XOR_Neural_Network XOR;
	for(;;)
	{
		printf("============================================================\n"\
                "Do you want to :\n"\
                "1.Train a new XOR neural network\n"\
				"2.Use a saved one\n"\
                "3.Quit\n"\
                "===========================================================\n"\
                );
        p = fgets(line,sizeof line, stdin);
        if(p == NULL)
            continue;
        err = sscanf(line, "%d",&choice);
		stop = 0;
        if(err == 1)
        {
		    switch(choice)
		    {
			    case 1:
				    NetworkInit(&XOR);
				    XOR_Train(&XOR);
				    break;
			    case 2:
				    if(access(".save_xor",F_OK) == 0)
				    {
					    XOR_Load(&XOR);
				    }
					else
					{
						stop = 1;
						printf("No Xor trained yet :(\n"\
								"You can train one or quit\n");
					}
				    break;
                case 3:
                    return 0;
			    default:
                    printf("Please input a number between 1 and 3");
			 	continue;
		    }
        }
        else
            continue;
		if(!stop)
        	break;
	}
	double a, b, res;
	for(;;)
	{
		printf("\nInput 2 integers a and b between 0 and 1 to calculate "\
                "a XOR b\nIf you want to quit : input 3\n\na = ");
        p = fgets(line, sizeof line, stdin);
        if(p == NULL)
            continue;
        err = sscanf(line, "%lf", &a);
		if(a == 3)
			break;
        printf("\nb = ");
        p = fgets(line, sizeof line, stdin);
        if(p == NULL)
            continue;
        err += sscanf(line,"%lf", &b);
		if(b == 3)
			break;
        if(err == 2 && (a==0 || a == 1) && (b==0 ||b==1))
        {
		    res = XOR_Calc(&XOR, a, b);
		    printf("\n%d XOR %d = %f\n",(int)a, (int)b, res);
        }
        else
            printf("\nInput must be 1 or 0\n");
	}
	return 0;
}
