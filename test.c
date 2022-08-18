int main(){
 
	int i,j,k,ll;
 
	for(i=0;i<6;i++){
		printf("%d",i);
	}
 
	k = 4;
	ll = 6;
	while(k>0){
		ll = ll + 3;
		k--;
	}
 
	printf("%d",ll);
	printf("%d",k);
	
	k = 4;
	ll = 6;
	
	while(k--){
		ll = ll + 3;
	}
 
	printf("%d",ll);
	printf("%d",k);
 
 
	return 0;
}
