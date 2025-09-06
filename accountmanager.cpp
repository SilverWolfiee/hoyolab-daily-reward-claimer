#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define JSON "accounts.json"
#define MAX_ACCOUNTS 10


	
typedef struct{
	char ltuid[256];
	char ltoken[256];
	char username[256];
}account;

account Accounts[MAX_ACCOUNTS];
int account_count = 0;

void saveAccounts(){
	FILE *fp = fopen("accounts.json", "w");
	if(!fp){
		printf("Account.json cannot be found\n");
		return;
	}
	fprintf(fp, "{\n  \"accounts\": [\n");
	for (int i = 0; i<account_count; i++){
		fprintf(fp, "    {\"ltuid\": \"%s\", \"ltoken\": \"%s\", \"username\": \"%s\"}%s\n",
		Accounts[i].ltuid,
		Accounts[i].ltoken,
		Accounts[i].username,
		(i < account_count - 1) ? "," : "");
	}
	fprintf(fp, "  ]\n}\n");
	fclose(fp);
}

void loadAccount(){
	FILE *fp = fopen("accounts.json", "r");
	if(!fp){
		printf("Account.json cannot be found\n");
		return;
	}
	char buffer[8192];
	size_t len = fread(buffer, 1, sizeof(buffer)-1, fp);
	buffer[len]= '\0';
	fclose(fp);
	account_count = 0;
	char *p =buffer;
	while ((p = strstr(p, "\"ltuid\"")) && account_count < MAX_ACCOUNTS) {
        account acc = {0};
		if (sscanf(p, "\"ltuid\": \"%255[^\"]\"", acc.ltuid) != 1) break;
		p = strstr(p, "\"ltoken\"");
        if (!p) break;
        if (sscanf(p, "\"ltoken\": \"%255[^\"]\"", acc.ltoken) != 1) break;
		p = strstr(p, "\"username\"");
        if (!p) break;
        if (sscanf(p, "\"username\": \"%255[^\"]\"", acc.username) != 1) break;
		Accounts[account_count++] = acc;
		p++;
	}
	printf("%d account(s) loaded.\n", account_count);
}

void addAccount(){
	system("cls");
	if(account_count>= MAX_ACCOUNTS){
		printf("Account has reach maximum\n");
		system("pause");
		return;
	}
	printf("Enter your Ltuid\n");
	printf("Read README.md to find Ltuid\n");
	printf(">> ");
	
	scanf("%s", Accounts[account_count].ltuid);
	printf("\nEnter your Ltoken\n");
	printf("Read README.md to find Ltoken\n");
	printf(">> ");	
	scanf("%s", Accounts[account_count].ltoken);
	printf("\nEnter your Username\n");
	printf(">> ");	
	scanf("%s", Accounts[account_count].username);


	account_count++;
	saveAccounts();
	printf("account has been added\n");
	system("pause");
}
void accountManager(){
	system("cls");
	for (int i = 0; i<account_count; i++){
		printf("%d. %s %s\n",i+1, Accounts[i].username, Accounts[i].ltuid);
		printf("------------------------\n");
	}
	
}
void removeAccount(){
	system("cls");
	if(account_count==0){
		printf("No accounts to remove\n");
		system("pause");
		return;
	}
	accountManager();
	int input = 0;
	while(input < 1 || input >account_count){
		printf("Select an account to remove\n");
		printf(">> ");
		scanf("%d", &input);
		if(input < 1 || input >account_count){
			printf("Invalid Selection\n");
			continue;
		}
	}
	for(int i = input -1; i<account_count -1 ; i++){
		Accounts[i] = Accounts[i+1];
	}
	account_count--;
	saveAccounts();
	printf("Account has been removed\n");
	system("pause");
	return;

}




int main(){
	loadAccount();
	while(1){
		system("cls");
		int input;
		printf("Hoyolab Account Manager\n");
		printf("=========================\n");
		printf("1. Add Account\n");
		printf("2. View saved Account\n");
		printf("3. Remove account\n");
		printf("4. Exit Program\n");
		printf(">>  ");
		scanf("%d", &input);
		if(1==input){
			addAccount();
		}
		else if(2 == input){
			accountManager();
			system("pause");
		}
		else if(3== input){
			removeAccount();
		}
		else if(4==input){
			break;
		}
	}
	
	
	
	system("cls");

	printf("Accounts Saved\n");
	system("pause");
	
	return 0;
}
