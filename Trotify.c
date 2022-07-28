#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>


typedef struct {
	char name1[60];
	char name2[60];
}NAME;

typedef struct {
    NAME names[127];
    char userID[50];
    char cardNumber[50];
    int tripNumber;
    int kmNumber;
}USER;

typedef struct {
    char vehicleID[100];
    int positionX;
    int positionY;
    int charge;
    int kmUntilMaintenance;
}VEHICLE;

typedef struct nodeUser * linkUser;
struct nodeUser {USER item; linkUser next;};

typedef struct nodeVehicle * linkVehicle;
struct nodeVehicle {VEHICLE item; linkVehicle next;};

typedef struct nodeVehicleCharge * linkVehicleCharge;
struct nodeVehicleCharge {char * item; linkVehicleCharge next;};

typedef struct nodeVehicleMaintenance * linkVehicleMaintenace;
struct nodeVehicleMaintenance {char * item; linkVehicleMaintenace next;};


int user_ID_existe (linkUser head, char * userID) {
	linkUser aux;
	for (aux = head ; aux != NULL ; aux = aux -> next) {
		if(strcmp(aux->item.userID, userID) == 0) {
			return 1;
		}
	}
	return 0;	
}

linkUser user_read_file (char path[], linkUser head) 
{
	char line [513];
	int idExiste;
	USER x;
	linkUser currentNode;
	linkUser temp;
	linkUser headNode;
	int i = 0;
	
	
	FILE * fp = fopen(path, "r");
	if (fp == NULL){
		fprintf(stderr, "Erro ao abrir o ficheiro\n");
	}else{
		while(fgets(line, 513, fp) != NULL) {
			sscanf(line,"%s %s %s %s %d %d",x.userID,x.names->name1,x.names->name2,x.cardNumber,&x.tripNumber,&x.kmNumber);
			idExiste = user_ID_existe(head, x.userID);
			if(strlen(x.userID) == 15 && strlen(x.cardNumber) == 24 && idExiste == 0){
				currentNode = (linkUser) malloc(sizeof(struct nodeUser));
				currentNode->item = x;
				if(i == 0) {
					headNode = temp = currentNode;
				}else{
					temp->next = currentNode;
					temp = currentNode;
				}
			}
			i = 1;
		}
		temp->next = NULL;
		temp = headNode;
		fclose(fp);
		return temp;
	}
	return 0;
}



int vehicle_ID_existe (linkVehicle head, char * vehicleID) {
	linkVehicle aux;
	for (aux = head ; aux != NULL ; aux = aux -> next) {
		if(strcmp(aux->item.vehicleID, vehicleID) == 0) {
			return 1;
		}
	}
	return 0;
}

linkVehicle maint_read_file (char path[],linkVehicle head) 
{
	char line [513];
	int idExiste;
	VEHICLE x;
	linkVehicle currentNode;
	linkVehicle temp;
	linkVehicle headNode;
	int i = 0;
	
	
	FILE * fp = fopen(path, "r");
	if (fp == NULL){
		fprintf(stderr, "Erro ao abrir o ficheiro\n");
	}else{
		while(fgets(line, 513, fp) != NULL) {
			sscanf(line,"%s %d %d %d %d",x.vehicleID,&x.positionX,&x.positionY,&x.charge,&x.kmUntilMaintenance);
			idExiste = vehicle_ID_existe(head, x.vehicleID);
			if(strlen(x.vehicleID) == 31 && idExiste == 0){
				currentNode = (linkVehicle) malloc(sizeof(struct nodeVehicle));
				currentNode->item = x;
				if(i == 0) {
					headNode = temp = currentNode;
					
				}else{
					temp->next = currentNode;
					temp = currentNode;
				}
			}
			i = 1;
		}
		temp->next = NULL;
		temp = headNode;
		fclose(fp);
		return temp;
	}
	return 0;
}	

int save_users(char path[], linkUser head) {
	linkUser aux;
	
	
	FILE * fp = fopen(path, "w");
	if (fp == NULL){
		fputs("Erro", stderr);
		return 1;
	}
	for(aux = head; aux != NULL; aux = aux->next) {
		fprintf(fp, "%s ",aux->item.userID);
		fprintf(fp, "%s ",aux->item.names->name1);
		fprintf(fp, "%s ",aux->item.names->name2);
		fprintf(fp, "%s ",aux->item.cardNumber);
		fprintf(fp, "%d ",aux->item.tripNumber);
		fprintf(fp, "%d\n",aux->item.kmNumber);
	}
	fclose(fp);
	return 0;
	
}	
int save_vehicles (char path[], linkVehicle head) {
	linkVehicle aux;
	
	FILE * fp = fopen(path, "w");
	if (fp == NULL){
		fputs("Erro", stderr);
		return 1;
	}
	for(aux = head; aux != NULL; aux = aux->next) {
		fprintf(fp, "%s ",aux->item.vehicleID);
		fprintf(fp, "%d ",aux->item.positionX);
		fprintf(fp, "%d ",aux->item.positionY);
		fprintf(fp, "%d ",aux->item.charge);
		fprintf(fp, "%d\n",aux->item.kmUntilMaintenance); 
	}
	fclose(fp);
	return 0;
}
	
linkUser userInsert(linkUser head){
	int i = 0;
	char name1 [30];
	char name2 [30];
	char userID [16];
	char cardNumber [25];
	int tripNumber, kmNumber;
	linkUser current = head;
	USER x;
	
		
	scanf(" %s %s %s %s %d %d", name1, name2, userID, cardNumber, &tripNumber, &kmNumber);
	i = user_ID_existe(head, userID);
	if (i == 1) {
		printf("User ID already exists\n");
	}
	if (strlen(userID) != 15 && strlen(cardNumber) != 24) {
		printf("Bad arguments\n");
	}else{
		strcpy(x.names->name1, name1);
		strcpy(x.names->name2, name2);
		strcpy(x.userID, userID);
		strcpy(x.cardNumber, cardNumber);
		x.tripNumber = tripNumber;
		x.kmNumber = kmNumber;
		if(current == NULL) {
			current = (linkUser) malloc(sizeof(struct nodeUser));
			current->item = x;
			current->next = NULL;
			return current;
		}else{
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = (linkUser) malloc(sizeof(struct nodeUser));
			current->next->item = x;
			current->next->next = NULL;
		}
	}
	return 0;
}

linkVehicle maintInsert(linkVehicle head){
	int i = 0;
	char vehicleID[100];
	int positionX, positionY, charge, kmUntilMaintenance;
	linkVehicle current = head;
	VEHICLE x;
	
	scanf(" %s %d %d %d %d", vehicleID, &positionX, &positionY, &charge, &kmUntilMaintenance);	
	i = vehicle_ID_existe(head, vehicleID);
	if (i == 1) {
		printf("Vehicle ID already exists\n");
	}
	if (strlen(vehicleID) != 31) {
		printf("Bad arguments\n");
	}else{
		strcpy(x.vehicleID, vehicleID);
		x.positionX = positionX;
		x.positionY = positionY;
		x.charge = charge;
		x.kmUntilMaintenance = kmUntilMaintenance;
		if(current == NULL) {
			current = (linkVehicle) malloc(sizeof(struct nodeVehicle));
			current->item = x;
			current->next = NULL;
			return current;
		}else{
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = (linkVehicle) malloc(sizeof(struct nodeVehicle));
			current->next->item = x;
			current->next->next = NULL;
		}
	}
	return 0;
}

int find_nearest_vehicle(linkVehicle head){
	if(head == NULL) {
		printf("No vehicle in memory\n");
	}else {
		char closestVehicleID[33];
		int userPositionX, userPositionY, smallestDistance = INT_MAX, distance;
		linkVehicle aux;
		scanf(" %d %d", &userPositionX, &userPositionY);
		for(aux = head; aux != NULL; aux = aux->next) {
			int positionX = userPositionX - aux->item.positionX;
			int positionY = userPositionY - aux->item.positionY;
			distance = pow(positionX,2) + pow(positionY,2);
			if(distance < smallestDistance && aux->item.charge > 20 && aux->item.kmUntilMaintenance > 3){
				smallestDistance = distance;
				strcpy(closestVehicleID, aux->item.vehicleID);
				
			}
		}
		printf("%s\n", closestVehicleID);
	}
	return 0;
}


int need_to_charge(linkVehicle head){
	int existe = 0;
	linkVehicle aux;
	for(aux = head; aux != NULL; aux = aux->next) {
		if(aux->item.charge < 20) {
			existe = 1;
			printf("%s\n", aux->item.vehicleID);
		}
	}
	if(existe == 0 || head == NULL) {
		printf("No vehicle needs to charge\n");
	}
	return 0;
}

int need_maintenance(linkVehicle head){
	int existe = 0;
	linkVehicle aux;
	for(aux = head; aux != NULL; aux = aux->next) {
		if(aux->item.charge < 20 || aux->item.kmUntilMaintenance < 3) {
			existe = 1;
			printf("%s\n", aux->item.vehicleID);
		}
	}
	if(existe == 0 || head == NULL) {
		printf("No vehicle needs maintenance\n");
	}
	return 0;
	

}

linkUser userDelete (linkUser head) {
	linkUser aux;
	linkUser aux2;
	linkUser aux3;
	int i;
	char userID [50];
	scanf (" %s", userID);
	i= user_ID_existe(head, userID);
	if(i == 0 || head == NULL) {
		printf("User ID does not exist\n");
	}else{
		if(strcmp(head->item.userID, userID) == 0) {		/*remove first*/
			aux = head;
			head = head -> next;
			aux -> next = NULL;
			if(aux == head) {
				head = NULL;
			}
			free(aux);
			printf("User %s removed\n", userID);
			return head;
		}else{
			for(aux = head; aux != NULL; aux = aux->next) {
			    if(strcmp(aux->item.userID,userID) == 0 && aux->next == NULL) {    /*remove back*/
					aux2 = head;
					aux3 = NULL;
					while(aux2->next != NULL) {
						aux3 = aux2;
						aux2 = aux2->next;
					}
					if(aux3 != NULL) {
						aux3->next = NULL;
					}
					if(aux2 == head) {
						head = NULL;
					}
					free(aux2);
					printf("User %s removed\n", userID);
					return head;
				}else{
					if(strcmp(aux->next->item.userID, userID) == 0) {     /* remove middle*/
						aux2 = aux->next;
						aux->next = aux2->next;
						free(aux2);
						printf("User %s removed\n", userID);
						return head;
					}
				}
			}
		}
	}
	return 0;
}
linkVehicle maintDelete(linkVehicle head) {
	linkVehicle aux;
	linkVehicle aux2;
	linkVehicle aux3;
	char vehicleID [70];
	int i;
	scanf(" %s", vehicleID);
	i = vehicle_ID_existe(head, vehicleID);
	if(i == 0 || head == NULL) {
		printf("Vehicle ID does not exist\n");
	}else{
		if(strcmp(head->item.vehicleID, vehicleID) == 0) { /*remove first */
			aux = head;
			head = head -> next;
			aux -> next = NULL;
			if(aux == head) {
				head = NULL;
			}
			free(aux);
			printf("Vehicle %s removed\n", vehicleID);
			return head;
		}else{
			for(aux = head; aux != NULL; aux = aux->next) {
			    if(strcmp(aux->item.vehicleID,vehicleID) == 0 && aux->next == NULL) {   /*remove back*/
					aux2 = head;
					aux3 = NULL;
					while(aux2->next != NULL) {
						aux3 = aux2;
						aux2 = aux2->next;
					}
					if(aux3 != NULL) {
						aux3->next = NULL;
					}
					if(aux2 == head) {
						head = NULL;
					}
					free(aux2);
					printf("Vehicle %s removed\n", vehicleID);
					return head;
				}else{
					if(strcmp(aux->next->item.vehicleID, vehicleID) == 0) { /* remove middle*/
						aux2 = aux->next;
						aux->next = aux2->next;
						free(aux2);
						printf("Vehicle %s removed\n", vehicleID);
						return head;
					}
				}
			}
		}
	}
	return 0;
}
int make_trip(linkVehicle headVehicle, linkUser headUser){
	char userID [100];
	char vehicleID[100];
	int endPositionX;
	int endPositionY;
	linkVehicle auxVehicle;
	linkUser auxUser;
	int positionX; 
	int positionY; 
	int cargaInicial;
	int kmUntilMaintenance;
	float dv; 
	int d; 
	int cargaFinal;
	float p;
	scanf(" %s %s %d %d",userID,vehicleID,&endPositionX,&endPositionY);
	for(auxVehicle = headVehicle; auxVehicle != NULL; auxVehicle = auxVehicle->next) {
		if(strcmp(auxVehicle->item.vehicleID, vehicleID) == 0) {
			positionX = auxVehicle->item.positionX;
			positionY = auxVehicle->item.positionY;
			cargaInicial = auxVehicle->item.charge;
			kmUntilMaintenance = auxVehicle->item.kmUntilMaintenance;
			dv = pow(pow((endPositionX-positionX),2)+pow((endPositionY-positionY),2),0.5);
			d = ceil(dv);
			cargaFinal = cargaInicial -100*((float)d/30);
			if (cargaFinal < 0){
				printf("Not possible to make such a long trip with this vehicle's charge\n");
			}else{
				auxVehicle->item.positionX = endPositionX; 
				auxVehicle->item.positionY = endPositionY; 
				auxVehicle->item.charge = cargaFinal; 
				kmUntilMaintenance = kmUntilMaintenance-d;
				auxVehicle->item.kmUntilMaintenance = kmUntilMaintenance;
				for(auxUser = headUser; auxUser!= NULL; auxUser = auxUser ->next) {
					if(strcmp(auxUser->item.userID, userID) == 0) {
						auxUser->item.tripNumber += 1;
						auxUser->item.kmNumber += d;
					}
				}
				p = 0.50 + 0.25 * d;
				if(p < 10){
					printf("%d 0%3.2f %d %d\n",d,p,kmUntilMaintenance,cargaFinal);
				}else{
					printf("%d %4.2f %d %d\n",d,p,kmUntilMaintenance,cargaFinal);
				}
			}
		}
	}
	return 0;

}
int maint_charge_vehicle(linkVehicle head) {
	int existeID = 0;
	linkVehicle aux;
	char vehicleID [100];
	scanf(" %s", vehicleID);
	for(aux = head; aux != NULL; aux = aux->next) {
		if(strcmp(aux->item.vehicleID, vehicleID) == 0){
			aux->item.charge = 100;
			existeID = 1;
		}
	}
	if(existeID == 0 || head == NULL) {
		printf("Vehicle ID does not exist\n");
	}
	return 0;
}
int charge_all_vehicles (linkVehicle head) {
	linkVehicle aux;
	for(aux = head; aux != NULL; aux= aux->next) {
		if(aux->item.charge < 20) {
			aux->item.charge = 100;
		}
	}
	return 0;
}
int maint_make_maintenance (linkVehicle head) {
	int existeID = 0;  
	linkVehicle aux;
	char vehicleID [100];
	scanf(" %s", vehicleID);
	for(aux = head; aux != NULL; aux = aux->next){
		if(strcmp(aux->item.vehicleID, vehicleID) == 0) {
			aux->item.kmUntilMaintenance = 50;
			existeID = 1;
		}
	}
	if(existeID == 0 || head == NULL) {
		printf("Vehicle ID does not exist\n");
	}
	return 0;
}
int make_maintenace_all_vehicles (linkVehicle head) {
	linkVehicle aux;
	for(aux = head; aux != NULL; aux = aux->next) {
		if(aux->item.kmUntilMaintenance < 3) {
			aux->item.kmUntilMaintenance = 50;
		}
	}
	return 0;
}


int menu (void) 
{
	printf("***********\n");
	printf("* Trotify *\n");
	printf("***********\n");
	printf("1.\n");
	printf("\ta. user read_file <path>\n");
	printf("\tb. user read_file\n");
	printf("2.\n");
	printf("\ta. maint read_file <path>\n");
	printf("\tb. maint read_file\n");
	printf("3.\n");
	printf("\ta. save_current_data <path>\n");
	printf("\tb. save_current_data\n");
	printf("4. user insert <name> <user_id> <card_number> <number_of_trip> <number_of_km>\n");
	printf("5. user find_nearest_vehicle <user_position_x> <user_position_y>\n");
	printf("6. maint insert <vehicle_id> <position_x> <position_y> <charge> <km_until_maintenance>\n");
	printf("7. maint need_to_charge\n");
	printf("8. maint need_maintenance\n");
	printf("9. user delete <user_id>\n");
	printf("10. maint delete <vehicle_id>\n");
	printf("11. user make_trip <user_id> <vehicle_id> <end_position_x> <end_position_y>\n");
	printf("12. maint charge_vehicle <vehicle_id>\n");
	printf("13. maint charge_all_vehicles\n");
	printf("14. maint make_maintenance <vehicle_id>\n");
	printf("15. maint make_maintenance_all_vehicles\n");
	printf("16. h\n");
	printf("17. q\n");
	return 0;
}

int main (int argc, char * argv[])
{
	int restart = 1;
	char enter;
	char option1 [50], option2 [50], pathUsers[100], pathVehicles[100];
	linkVehicle vehicleList = NULL;
	linkUser userList = NULL;
	menu();
	do{
		scanf("%s", option1);
		if (strcmp(option1, "user") == 0) {
			scanf(" %s", option2);
			if(strcmp(option2, "read_file") == 0){
				scanf("%c",&enter);
				if(enter == '\n') {
					if(argc == 2) {
						char extensao[6] = ".users";
						strcpy(pathUsers, argv[1]);
						strcpy(pathUsers,strcat(pathUsers, extensao));
						userList = user_read_file(pathUsers, userList);
					} else {
						printf("No path to file defined\n");
					}
				}else{
					char extensao[6] = ".users";
					scanf("%s", pathUsers);
					strcat(pathUsers, extensao);
					userList = user_read_file(pathUsers, userList);
				}
			
		    }

			if(strcmp(option2, "insert") == 0){
				 if(userList == NULL) {
					userList = userInsert(userList);
				}else{
					userInsert(userList);
				}
			}

			if(strcmp(option2, "find_nearest_vehicle") == 0){
				find_nearest_vehicle(vehicleList);
				
			}
			if(strcmp(option2, "delete") == 0) {
				userList = userDelete(userList);
			}
			if(strcmp(option2, "make_trip") == 0) {
				make_trip(vehicleList, userList);
			}
		}

		if (strcmp(option1, "maint") == 0) {
			scanf(" %s", option2);
			if (strcmp(option2, "read_file") == 0){
				scanf("%c",&enter);
				if(enter == '\n') {
					if(argc == 2) {
						char extensao[13] = ".trotinetes";
						strcpy(pathVehicles, argv[1]);
						strcpy(pathVehicles,strcat(pathVehicles, extensao));
						vehicleList = maint_read_file(pathVehicles, vehicleList);
					} else {
						printf("No path to file defined\n");
					}
				}else{
					char extensao[13] = ".trotinetes";
					scanf("%s", pathVehicles);
					strcat(pathVehicles, extensao);
					vehicleList = maint_read_file(pathVehicles, vehicleList);
				}
					
		 	}

			if (strcmp(option2, "insert") == 0){
				if(vehicleList == NULL) {
					vehicleList = maintInsert(vehicleList);
				}else{
					maintInsert(vehicleList);
				}
				
			}

			if (strcmp(option2, "need_to_charge") == 0){
				need_to_charge(vehicleList);
			}

			if (strcmp(option2, "need_maintenance") == 0){
				need_maintenance(vehicleList);
			}
			if (strcmp(option2, "delete") == 0) {
				vehicleList = maintDelete(vehicleList);
			}
			if(strcmp(option2, "charge_vehicle") == 0) {
				maint_charge_vehicle(vehicleList);
			}
			if(strcmp(option2, "charge_all_vehicles") == 0) {
				charge_all_vehicles(vehicleList);
			}
			if(strcmp(option2, "make_maintenance") == 0) {
				maint_make_maintenance(vehicleList);
			}
			if(strcmp(option2, "make_maintenance_all_vehicles") == 0) {
				make_maintenace_all_vehicles(vehicleList);
			}
		}
		if(strcmp(option1, "save_current_data") == 0) {
			scanf("%c",&enter);
			if(enter == '\n'){
				
				if(argc == 2) {
					char extensao1[9] = ".userout";
					char extensao2[15] = ".trotinetesout";
					char path1[50];
					char path2[50]; 
					strcpy(path1, argv[1]);
					strcpy(path2, argv[1]);
					strcpy(path1,strcat(path1, extensao1));
					strcpy(path2,strcat(path2, extensao2));
					save_users(path1, userList);
					save_vehicles(path2, vehicleList); 
				}else{
					printf("No path to file defined\n");
				}
			}else{
				char extensao1[9] = ".userout";
				char extensao2[15] = ".trotinetesout";
				char path1[50];
				char path2[50];
				scanf("%s", option2);
				strcpy(path1,strcat(option2, extensao1));
				strcpy(path2,strcat(option2, extensao2));
				save_users(path1, userList);
				save_vehicles(path2,vehicleList);
			}
		
		}
		if (strcmp(option1, "h") == 0) {
			menu();
		}
		if (strcmp(option1, "q") == 0) {
			restart = 0;
		}
	}while(restart == 1);
exit(0);
}
