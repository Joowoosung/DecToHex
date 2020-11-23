#include "bigint.h"

int reverseChar(char* a,int len) {
	char tmp;
	int i = 0;
	
	for (i = 0; i < len / 2; i++) {
		tmp = a[i];
		a[i] = a[len - i - 1];
		a[len - i - 1] = tmp;
	}

	return 0;

}

int makeBigInt(char input[201], char* ret)
{
	char input2[201] = "1000000000000000000";
	char tmp[201];
	char operation;
	int i, j, k = 0;
	int cnt = 0;
	struct BigNum object[6];
	j = 0;
	enter_number(input, &object[0]);
	
	memset(&tmp, 0x00, sizeof(tmp));
	for (;;)
	{
			enter_number(input2, &object[1]);
			multiple(&object[0], &object[1], &object[2]);
			//printf("결과를 출력합니다. \n");
			if (object[2].sign < 0)
			{
				//printf("-");
			}
			if (object[2].i_total_digit > 100)
			{
				for (i = 0; i < object[2].i_total_digit - 100; i++)
				{
					//printf("%d", object[2].i_digit_add[object[2].i_total_digit - 100 - 1 - i]);
				}
				for (i = 0; i < 100; i++)
				{
					//printf("%d", object[2].i_digit[99 - i]);
				}
			}
			else
			{
				for (i = 0; i < object[2].i_total_digit; i++)
				{
					//printf("%d", object[2].i_digit[object[2].i_total_digit - i - 1]);
				}
			}
			if (object[2].d_total_digit > 0)
			{
				//printf(".");
			}
			if (object[2].d_total_digit > 100)
			{
				for (i = 0; i < 100; i++)
				{
					//printf("%d", object[2].d_digit[99 - i]);
				}
				for (i = 0; i < object[2].d_total_digit - 100; i++)
				{
					//printf("%d", object[2].d_digit_add[object[2].d_total_digit - 100 - 1 - i]);
				}
			}
			else
			{
				for (i = 0; i < object[2].d_total_digit; i++)
				{
					//printf("%d", object[2].d_digit[object[2].d_total_digit - i - 1]);
				}
			}
			//printf("\n");
			object[3] = object[0];
			object[0] = object[2];
			
			for (i = 0; i < object[0].i_total_digit; i++)
			{
				if(i == 0 )
					sprintf_s(tmp, 2, "%d", object[0].i_digit[object[0].i_total_digit - i - 1]);
				else
					sprintf_s(tmp, 2+i ,"%s%d", tmp, object[0].i_digit[object[0].i_total_digit - i - 1]);
				
			}
			
			
			strcpy_s(ret, 201, tmp);
			break;
	}
	return 0;
}


int makeBinary(char input[201], char* ret)
{
	char input2[201] = "2";
	char operation;
	int i,j,k = 0;
	int cnt = 0;
	struct BigNum object[6];
	j = 0;
	enter_number(input, &object[0]);
	for(;;)
	{
			if (object[0].i_digit[0] % 2 == 0) {
				ret[cnt] = '0';
			}
			else {
				ret[cnt] = '1';
			}
			enter_number(input2, &object[1]);
			if(k<=100)
			{
				divide(&object[0], &object[1], &object[2], &object[3], &object[4],&object[5], &k);
			}
			else
			{
				//printf("연산 가능한 범위를 벗어납니다. \n");
				continue;
			}
			//printf("결과를 출력합니다. \n");
			if(object[2].sign < 0)
			{
				//printf("-");
			}
			if(object[2].i_total_digit>100)
			{
				for(i=0;i<object[2].i_total_digit-100;i++)
				{
					//printf("%d", object[2].i_digit_add[object[2].i_total_digit-100-1-i]);
				}
				for(i=0;i<100;i++)
				{
					//printf("%d", object[2].i_digit[99-i]);
				}
			}
			else
			{
				for(i=0;i<object[2].i_total_digit;i++)
				{
					//printf("%d", object[2].i_digit[object[2].i_total_digit-i-1]);
				}
			}
			if(object[2].d_total_digit>0)
			{
				//printf(".");
			}
			if(object[2].d_total_digit>100)
			{
				for(i=0;i<100;i++)
				{
					//printf("%d", object[2].d_digit[99-i]);
				}
				for(i=0;i<object[2].d_total_digit-100;i++)
				{
					//printf("%d", object[2].d_digit_add[object[2].d_total_digit-100-1-i]);
				}
			}
			else
			{
				for(i=0;i<object[2].d_total_digit;i++)
				{
					//printf("%d", object[2].d_digit[object[2].d_total_digit-i-1]);
				}
			}
			//printf("\n");
			object[3]=object[0];
			object[0]=object[2];

			cnt++;

			if (object[0].i_total_digit == 1 && object[0].i_digit[0] == 1) {
				//printf("total_digit %d\n", object[0].i_total_digit);
				ret[cnt] = '1';
				break;
			}else if (object[0].i_total_digit == 1 && object[0].i_digit[0] == 0) {
				//printf("total_digit %d\n", object[0].i_total_digit);
				ret[cnt] = '0';
				break;
			}

	}
	return 0;
}


int enter_number(char *input, struct BigNum *object)
{
	int i,j,l;
	i=j=l=0;
	object->i_total_digit=0;
	object->d_total_digit=0;
	if(*input =='-')
	{
		input++;
		while(*input!='.'&&*input !='\0')
		{
			i++;
			input++;
		}
		j=i;
		input=input-i;
		i=0;
		for(i=0;i<j;i++)
		{
			object->i_digit[j-i-1]=(int) *input-48;
			object->i_total_digit++;
			input++;
		}
		if(*input != '\0')
		{
			input++;
		}
		while(*input)
		{
			object->d_total_digit++;
			l++;
			input++;
		}
		input=input-l;
		for(i=0;i<l;i++)
		{
			object->d_digit[l-i-1]=(int) *input-48;
			input++;
		}
		input=input-object->i_total_digit-object->d_total_digit-2;
		l=0;
		object->sign=-1;
	}
	else
	{
		while(*input!='.' && *input !='\0')
		{
			i++;
			input++;
		}
		j=i;
		input=input-i;
		i=0;
		for(i=0;i<j;i++)
		{
			object->i_digit[j-i-1]=(int) *input-48;
			object->i_total_digit++;
			input++;
		}
		if(*input == '.')
		{
			input++;
		}
		while(*input)
		{
			object->d_total_digit++;
			l++;
			input++;
		}
		input=input-l;
		for(i=0;i<l;i++)
		{
			object->d_digit[l-i-1]=(int) *input-48;
			input++;
		}
		input=input-object->i_total_digit-object->d_total_digit-1;
		l=0;
		object->sign=1;
	}
	return 0;
}
int compare_number(struct BigNum *object, struct BigNum *object2)
{
	int i,j,k;
	j=0; k=0;
	for(i=0;i<400;i++)
	{
		if(object->i_total_digit > object2->i_total_digit)
		{
			j=1;
			k=1;
			break;
		}
		else if(object2->i_total_digit > object->i_total_digit)
		{
			j=1;
			k=2;
			break;
		}
		else if(object2->i_total_digit == object->i_total_digit)
		{
			if(object->i_digit[object->i_total_digit-i-1] > object2->i_digit[object2->i_total_digit-i-1])
			{
				j=1;
				k=1;
				break;
			}
			else if(object2->i_digit[object2->i_total_digit-i-1] > object->i_digit[object->i_total_digit-i-1])
			{
				j=1;
				k=2;
				break;
			}
			else if(object2->i_digit[object2->i_total_digit-i-1] == object->i_digit[object->i_total_digit-i-1])
			{
				if(i>object->i_total_digit || i>object2->i_total_digit)
				{
					i=0;
					break;
				}
				else if(object->i_digit[0]==0 && object->i_total_digit==1)
				{
					i=0;
					break;
				}
			}
		}
	}
	if(j == 0)
	{
		for(;;)
		{
			if(object->d_digit[object->d_total_digit-1-i] > object2->d_digit[object2->d_total_digit-1-i])
			{
				j=1;
				k=1;
				break;
			}
			else if(object2->d_digit[object2->d_total_digit-1-i] > object->d_digit[object->d_total_digit-1-i])
			{
				j=1;
				k=2;
				break;
			}
			else
			{
				if(i<object->d_total_digit && i<object2->d_total_digit)
				{
					i++;
				}
				else
				{
					if(object->d_total_digit == object2->d_total_digit)
					{
						j=1;
						k=0;
						break;
					}
					else if(object->d_total_digit > object2->d_total_digit)
					{
						j=1;
						k=1;
						break;
					}
					else
					{
						j=1;
						k=2;
						break;
					}
				}
			}
		}
	}
	return k;
}
int plus(struct BigNum *object, struct BigNum *object2, struct BigNum *object3)
{
	int i,j,k,m = 0;
	m=0;
	if(object->d_total_digit > object2->d_total_digit)
	{
		for(j=0;j<object2->d_total_digit;j++)
		{
			object3->d_digit[j+object2->d_total_digit] = object2->d_digit[j]+object->d_digit[j+object2->d_total_digit];
		}
		object3->d_total_digit = object->d_total_digit;
	}
	else if(object->d_total_digit==object2->d_total_digit)
	{
		for(i=0;i<object2->d_total_digit;i++)
		{
			object3->d_digit[i]=object->d_digit[i]+object2->d_digit[i];
		}
		object3->d_total_digit = object2->d_total_digit;
	}
	else
	{
		k=object2->d_total_digit-object->d_total_digit;
		for(j=0;j<object->d_total_digit;j++)
		{
			object3->d_digit[j+k] = object->d_digit[j]+object2->d_digit[j+k];
		}
		for(j=0;j<object2->d_total_digit;j++)
		{
			object3->d_digit[j] = object2->d_digit[j];
		}
		object3->d_total_digit = object2->d_total_digit;
	}
	if(object->i_total_digit>object2->i_total_digit)
	{
		for(j=0;j<object2->i_total_digit;j++)
		{
			object3->i_digit[j] = object->i_digit[j]+object2->i_digit[j];
		}
		for(j=object2->i_total_digit;j<object->i_total_digit;j++)
		{
			object3->i_digit[j] = object->i_digit[j];
		}
		object3->i_total_digit = object->i_total_digit;
	}
	else if(object->i_total_digit==object2->i_total_digit)
	{
		for(j=0;j<object->i_total_digit;j++)
		{
			object3->i_digit[j] = object->i_digit[j]+object2->i_digit[j];
		}
		object3->i_total_digit = object2->i_total_digit;
	}
	else
	{
		for(j=0;j<object->i_total_digit;j++)
		{
			object3->i_digit[j] = object->i_digit[j]+object2->i_digit[j];
		}
		for(j=object->i_total_digit;j<object2->i_total_digit;j++)
		{
			object3->i_digit[j] = object2->i_digit[j];
		}
		object3->i_total_digit = object2->i_total_digit;
	}
	for(j=0;j<object3->d_total_digit;j++)
	{
		if(object3->d_digit[j]>9)
		{
			object3->d_digit[j] = object3->d_digit[j]-10;
			if(j==object3->d_total_digit-1)
			{
				if(object3->i_digit[0] >=0 && object3->i_digit[0] < 20)
				{
					object3->i_digit[0] = object3->i_digit[0]+1;
				}
				else
				{
					object3->i_digit[0] = 1;
				}
			}
			else
			{
				object3->d_digit[j+1] = object3->d_digit[j+1]+1;
			}
		}
	}
	for(j=0;j<object3->i_total_digit;j++)
	{
		if(object3->i_digit[j]>9)
		{
			object3->i_digit[j]=object3->i_digit[j]-10;
			if(j==99)
			{
				object3->i_digit_add[0]=1;
				object3->i_total_digit++;
			}
			else
			{
				if(object3->i_digit[j+1]<20 && object3->i_digit[j+1]>=0)
				{
					object3->i_digit[j+1]++;
				}
				else
				{
					object3->i_digit[j+1]=1;
					object3->i_total_digit++;
				}
			}
		}
	}
	if(object3->d_digit[0] == 0)
	{
		object3->d_total_digit--;
		for(j=1;j<object3->d_total_digit;j++)
		{
			if(object3->d_digit[j] == 0)
			{
				object3->d_total_digit--;				
			}
			else
			{
				break;
			}
		}
	}
	object3->sign = object->sign;
	return 0;
}
int multiple(struct BigNum *object, struct BigNum *object2, struct BigNum *object3)
{
	int i,j,k,l,m,n,o = 0;
	int obj_num[200], obj2_num[200], obj3_num[400];
	for(i=0;i<object->d_total_digit;i++)
	{
		obj_num[i]=object->d_digit[i];
	}
	for(i=0;i<object->i_total_digit;i++)
	{
		obj_num[i+object->d_total_digit]=object->i_digit[i];
	}
	for(i=0;i<object2->d_total_digit;i++)
	{
		obj2_num[i]=object2->d_digit[i];
	}
	for(i=0;i<object2->i_total_digit;i++)
	{
		obj2_num[i+object2->d_total_digit]=object2->i_digit[i];
	}
	object3->d_total_digit=object->d_total_digit+object2->d_total_digit;
	object3->i_total_digit=object->i_total_digit+object2->i_total_digit;
	if(object->i_digit[object->i_total_digit-1]*object2->i_digit[object2->i_total_digit-1])
	{
		object3->i_total_digit++;
	}
	for(i=0;i<object3->i_total_digit+object3->d_total_digit;i++)
	{
		obj3_num[i]=0;
	}
	for(i=0;i<object2->d_total_digit+object2->i_total_digit;i++)
	{
		for(j=0;j<object->d_total_digit+object->i_total_digit;j++)
		{
			k=obj_num[j]*obj2_num[i];
			l=k/10;
			n=k%10;
			obj3_num[i+j]=obj3_num[i+j]+n;
			obj3_num[i+j+1]=obj3_num[i+j+1]+l;
			if(obj3_num[i+j]>9)
			{
				obj3_num[i+j]=obj3_num[i+j]-10;
				obj3_num[i+j+1]++;
			}
			if(obj3_num[i+j+1]>9)
			{
				obj3_num[i+j+1]=obj3_num[i+j+1]-10;
				obj3_num[i+j+2]++;
			}
		}
	}
	if(object3->d_total_digit>100 && object3->i_total_digit>100)
	{
		for(i=0;i<object3->d_total_digit-100;i++)
		{
			object3->d_digit_add[i]=obj3_num[i];
		}
		for(i=0;i<100;i++)
		{
			object3->d_digit[i]=obj3_num[i+object3->d_total_digit-100];
			object3->i_digit[i]=obj3_num[i+object3->d_total_digit];
		}
		for(i=0;i<object3->i_total_digit-100;i++)
		{
			object3->i_digit_add[i]=obj3_num[i+object3->d_total_digit+object3->i_total_digit-100];
		}
	}
	else if(object3->d_total_digit>100 && object3->i_total_digit<=100)
	{
		for(i=0;i<object3->d_total_digit-100;i++)
		{
			object3->d_digit_add[i]=obj3_num[i];
		}
		for(i=0;i<100;i++)
		{
			object3->d_digit[i]=obj3_num[i+object3->d_total_digit-100];
		}
		for(i=0;i<object3->i_total_digit;i++)
		{
			object3->i_digit[i]=obj3_num[i+object3->d_total_digit];
		}
	}
	else if(object3->d_total_digit<=100 && object3->i_total_digit>100)
	{
		for(i=0;i<object3->d_total_digit;i++)
		{
			object3->d_digit[i]=obj3_num[i];
		}
		for(i=0;i<100;i++)
		{
			object3->i_digit[i]=obj3_num[i+object3->d_total_digit];
		}
		for(i=0;i<object3->i_total_digit-100;i++)
		{
			object3->i_digit_add[i]=obj3_num[i+object3->d_total_digit+object3->i_total_digit-100];
		}
	}
	else
	{
		for(i=0;i<object3->d_total_digit;i++)
		{
			object3->d_digit[i]=obj3_num[i];
		}	
		for(i=0;i<object3->i_total_digit;i++)
		{
			object3->i_digit[i]=obj3_num[i+object3->d_total_digit];
		}
	}
	if(object3->d_total_digit>100)
	{
		for(i=0;i<object3->d_total_digit-100;i++)
		{
			if(object3->d_digit_add[i]==0)
			{
				for(j=0;j<object3->d_total_digit-100;j++)
				{
					object3->d_digit_add[j]=object3->d_digit_add[j+1];
				}
				object3->d_total_digit--;
			}
			else
			{
				m=0;
				break;
			}
		}
		if(m != 0)
		{
			for(i=0;i<100;i++)
			{
				if(object3->d_digit[i]==0)
				{
					for(j=0;j<object3->d_total_digit;j++)
					{
						object3->d_digit[j]=object3->d_digit[j+1];
					}
					object3->d_total_digit--;
				}
				else
				{
					m=1;
					break;
				}
			}
		}
	}
	else
	{
		for(i=0;i<object3->d_total_digit;i++)
		{
			if(object3->d_digit[i]==0)
			{
				for(j=0;j<object3->d_total_digit;j++)
				{
					object3->d_digit[j]=object3->d_digit[j+1];
				}
				object3->d_total_digit--;
			}
			else
			{
				break;
			}
		}
	}
	if(object3->i_total_digit>100)
	{
		for(i=0;i<object3->i_total_digit-100;i++)
		{
			if(object3->i_digit_add[i]==0)
			{
				object3->i_total_digit--;
			}
			else
			{
				m=0;
				break;
			}
		}
		if(m!=0)
		{
			for(i=0;i<100;i++)
			{
				if(object3->i_digit[99-i]==0)
				{
					object3->i_total_digit--;
				}
				else
				{
					m=1;
					break;
				}
			}
		}
	}
	else
	{
		o=object3->i_total_digit;
		for(i=0;i<object3->i_total_digit;i++)
		{
			if(object3->i_digit[o-1-i]==0)
			{
				object3->i_total_digit--;
			}
			else
			{
				break;
			}
		}
	}
	object3->sign=object->sign * object2->sign;
	return 0;
}
int divide(struct BigNum *object, struct BigNum *object2, struct BigNum *object3, struct BigNum *object4, struct BigNum *object5,struct BigNum *object6, int *d_total)
{
	int i,j,k,l = 0;
	int a, b, c,d,e;
	a=object->sign;
	b=object2->sign;
	c=d=0; e=0;
	j=k=l=0;
	object->sign=1; object2->sign=1;
	object3->i_total_digit=object3->d_total_digit=0;
	*object6=*object;
	*object4=*object2;
	if(object->i_total_digit==1 && object->i_digit[0]==0)
	{
		d++;
		object->i_digit[0]=object->d_digit[object->d_total_digit-1];
		for(i=0;i<object->d_total_digit;i++)
		{
			object->d_digit[object->d_total_digit-1-i]=object->d_digit[object->d_total_digit-1-i];
		}
		object->d_digit[0]=0;
	}
	if(object2->i_total_digit==1 && object2->i_digit[0]==0)
	{
		for(i=0;i<100;i++)
		{
			if(object4->d_digit[object->d_total_digit-1-i]==0)
			{
				e++;
			}
			else
			{
				break;
			}
		}
		object4->i_digit[0]=object4->d_digit[object4->d_total_digit-1-e];
		for(i=0;i<object4->d_total_digit;i++)
		{
			object4->d_digit[object4->d_total_digit-1-i]=object4->d_digit[object4->d_total_digit-1-i-e];
		}
		for(i=0;i<e;i++)
		{
			object4->d_digit[i]=0;
		}
		if(e==0)
		{
			object4->d_digit[0]=0;
			d--;
		}
		d=d-e;
	}
	for(i=0;i<object4->i_total_digit;i++)
	{
		object4->i_digit[object->i_total_digit-1-i]=object4->i_digit[object4->i_total_digit-1-i];
	}
	for(i=0;i<object->i_total_digit-object4->i_total_digit;i++)
	{
		if(object4->d_digit[object4->d_total_digit-1-i]>=0 && object4->d_digit[object4->d_total_digit-1-i]<10)
		{
			object4->i_digit[object->i_total_digit-object4->i_total_digit-1-i]=object4->d_digit[object4->d_total_digit-1-i];
		}
		else
		{
			object4->i_digit[object->i_total_digit-object4->i_total_digit-1-i]=0;
		}
	}
	for(i=0;i<object->i_total_digit-object4->i_total_digit;i++)
	{
		object4->d_digit[object4->d_total_digit-1-i]=0;
	}
	object4->d_total_digit=object2->d_total_digit-object->i_total_digit+object2->i_total_digit;
	object4->i_total_digit=object->i_total_digit;
	for(;;)
	{
		*object5=*object;
		if(object->d_total_digit>object4->d_total_digit)
		{
			for(i=object->d_total_digit-object4->d_total_digit;i<object->d_total_digit;i++)
			{
				object->d_digit[i]=object->d_digit[i]-object4->d_digit[i-object->d_total_digit+object4->d_total_digit];
			}
		}
		else
		{
			for(i=0;i<object4->d_total_digit-object->d_total_digit;i++)
			{
				object->d_digit[i]=0-object4->d_digit[i];
			}
			for(i=object4->d_total_digit-object->d_total_digit;i<object4->d_total_digit;i++)
			{
				object->d_digit[i]=object->d_digit[i]-object4->d_digit[i-object4->d_total_digit+object->d_total_digit];
			}
			object->d_total_digit=object4->d_total_digit;
		}
		for(i=0;i<object->d_total_digit;i++)
		{
			if(object->d_digit[i]<0 && i!=object->d_total_digit-1)
			{
				object->d_digit[i]=object->d_digit[i]+10;
				object->d_digit[i+1]--;
			}
			else if(object->d_digit[i]<0 && i==object->d_total_digit-1)
			{
				object->d_digit[i]=object->d_digit[i]+10;
				object->i_digit[0]--;
			}
		}
		for(i=0;i<object->i_total_digit;i++)
		{
			object->i_digit[i]=object->i_digit[i]-object4->i_digit[i];
		}
		for(i=0;i<object->i_total_digit;i++)
		{
			if(object->i_digit[i]<0 && i!=object->i_total_digit-1)
			{
				object->i_digit[i]=object->i_digit[i]+10;
				object->i_digit[i+1]--;
			}
			else if(object->i_digit[i]<0 && i==object->i_total_digit-1)
			{
				if(object->i_digit[i+1]>0 && object->i_digit[i+1]<10)
				{
					object->i_digit[i]=object->i_digit[i]+10;
					object->i_digit[i+1]--;
				}
			}
		}
		c++;			
		if(object->i_digit[object->i_total_digit-1]<0)
		{
			*object=*object5;
			if(d<=object->i_total_digit-object2->i_total_digit)
			{
				object3->i_digit[object->i_total_digit-object2->i_total_digit-d]=c-1;
				object3->i_total_digit++;
			}
			else
			{
				object3->d_digit[*d_total-d+object->i_total_digit-object2->i_total_digit]=c-1;
				object3->d_total_digit++;
			}
			for(i=0;i<object->i_total_digit;i++)
			{
				object->i_digit[object->i_total_digit-i]=object->i_digit[object->i_total_digit-1-i];
			}
			if(object->d_digit[object->d_total_digit-1]>=0 &&object->d_digit[object->d_total_digit-1]<10)
			{
				object->i_digit[0]=object->d_digit[object->d_total_digit-1];
			}
			else
			{
				object->i_digit[0]=0;
			}
			for(i=0;i<object->d_total_digit-1;i++)
			{
				object->d_digit[object->d_total_digit-1-i]=object->d_digit[object->d_total_digit-2-i];
			}
			object->d_digit[0]=0;
			d++;
			c=0;
		}
		if(d-object->i_total_digit+object2->i_total_digit>*d_total)
		{
			break;
		}
	}
	for(i=0;i<object3->d_total_digit;i++)
	{
		if(object3->d_digit[i]==0)
		{
			l++;
		}
		else
		{
			break;
		}
	}
	for(i=0;i<object3->d_total_digit;i++)
	{
		object3->d_digit[i]=object3->d_digit[i+l];
	}
	object3->d_total_digit=object3->d_total_digit-l;
	l=0;
	for(i=0;i<object3->i_total_digit;i++)
	{
		if(object3->i_digit[object3->i_total_digit-1-i]==0)
		{
			l++;
		}
		else
		{
			break;
		}
	}
	object3->i_total_digit=object3->i_total_digit-l;
	l=0;
	object3->sign=a*b;
	*object=*object6;
	return 0;
}