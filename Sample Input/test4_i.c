int a,b,c;

void func_a(){
	a = 7;
}

int foo(int a){
	a = a + 3;
	return a;
}

int bar(int a, int b){
	int c;
	c = 4*a + 2*b;
	return c;
}


int main(){
 
	int i,j,k,l;
	
	i = 5;
	j = 6;
	
	func_a();
	printf("%d\n",a);
	
	k = foo(i);
	printf("%d\n",k);
	
	l = bar(i,j);
	printf("%d\n",l);
	
	j = 6 * bar(i,j) + 2 - 3 * foo(i);
	printf("%d\n",j);
	
 
	return 0;
}

