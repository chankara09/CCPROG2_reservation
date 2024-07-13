/******************************************************************************
This is to certify that this project is my own & partners work, based on
my/our personal efforts in studying and applying the concepts learned. I/we
have constructed the functions and their respective algorithms and
corresponding code by me (and my partner). The program was run, tested, and
debugged by my own efforts. I further certify that I have not copied in
part or whole or otherwise plagiarized the work of other students and/or
persons.
Laurize Jeante G. Wangkay - 12278599 - S13
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USERS 100
typedef char nString[100];

struct Name
{
	nString First;
	nString Last;	
};
typedef struct Name Name;

struct ReservedSlot
{
	int isReserved; //reservation flag (1 or 0) if 1 (reserved) if not (not reserved)
};
typedef struct ReservedSlot ReservedSlot; 

struct ClassroomA
{
	nString Desc; //description for activity
	int participants;
	ReservedSlot reservation;
};
typedef struct ClassroomA ClassroomA;

struct classroomType
{
	//int Classroom; //3 types of classroom
	nString Code; //classroom code
	ClassroomA type; 
};
typedef struct classroomType classroomType;

struct classroomFloor
{
	int Floor; // 3 floors
	classroomType nClassroom;
};
typedef struct classroomFloor classroomFloor;

struct Date3
{
	int Time1;//1st timeslot
	int Time2; //2nd timeslot
	classroomFloor nFloor;
	//int Time; //a struct in a day of a classroom	
};
typedef struct Date3 Date3;

struct Date2
{
	int Day; //a struct in a week
	Date3 nTime;
};
typedef struct Date2 Date2;

struct Date1
{
	int Week; //3 weeks only 
	Date2 nDay;
};
typedef struct Date1 Date1;

typedef struct Users
{
	int databaseNum; //pang-ilan cla sa database
	int IDnum; //userID
	Name FLName; //First and Lastname
	nString Program; //Program (initial only)
	int Year; //Year
	int Max; //maximum amount of reservations
	Date1 Date;
	
}Users;

typedef Users Person[MAX_USERS]; //people that wants to make a reservation

/* reserveRoom3 is the final stage of reserving a room, it checks whether the user did not exceed the maximum of 3
				reservation limit and the user does not pick the same date, time, floor and classroom of the other 
				users. If it is cleared then it will add a new user to the struct.
@param user - People User struct
@param numUser - amount of people currently on the database struct
@param userparticipant - temporary data for the user input of participants
@param userweek - temporary data for the user input of the week number
@param userday - temporary data for the user input of the day number
@param usertimeslot - temporary data for the user input of the time slot
@param userfloor - temporary data for the user input of the level of the floor
@param combination1 - temporary data for the user input of classroom code
Pre-condition: Does not hit an invalid or again
*/

void reserveRoom3(Person user, int *numUser, int userparticipant, int userweek, int userday, int usertimeslot, int userfloor, char *combination1)
{
	int j, k, temp = 0, limit = 0, found = 0, bStop = 0, check = 0; //initializer for reserved slot
	nString tempDesc;
	do{
		do{
			printf("Description for the purpose of reserving your room?\n");
			fgets(tempDesc, sizeof(tempDesc), stdin);
			tempDesc[strlen(tempDesc)-1] = '\0';
			if(tempDesc[0] == '\0'){
				printf("You can't have an empty description.\n");
				getch();
			}
		}while(tempDesc[0] == '\0');
		strcpy(user[*numUser].Date.nDay.nTime.nFloor.nClassroom.type.Desc, tempDesc);
		user[*numUser].Date.nDay.nTime.nFloor.nClassroom.type.participants = userparticipant;
		for(k = 0; k < *numUser; k++){
			if(user[k].Date.Week == userweek && user[k].Date.nDay.Day == userday && user[k].Date.nDay.nTime.Time1 == usertimeslot && user[k].Date.nDay.nTime.nFloor.Floor == userfloor && strcmp(user[k].Date.nDay.nTime.nFloor.nClassroom.Code, combination1) == 0 && user[k].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved == 1){
			printf("There has been a reservation made here.\n");
			getch();
			bStop = 1;
			check = 1;
			}
		}
		if(check == 1){
			bStop = 1;
		}					
		else{
			user[*numUser].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved = 1;
			printf("Reserved!\n");
			printf("Admin Note: If you would like to make changes with your reservation,\n\t    encode your ID number provided by the system.\n");
			user[*numUser].databaseNum = *numUser;
			printf("Here is your ID number, %s: %d", user[*numUser].FLName.First, user[*numUser].databaseNum);
			user[*numUser].Max = 1;
			for(j = 0; j < *numUser; j++){
				if(user[j].IDnum == user[*numUser].IDnum){
					user[j].Max += 1;
					temp = user[j].Max;
					found = 1;
					if(user[j].Max == 4){
						limit = 1;
					}
				}
			}
			if(found == 1){
				user[*numUser].Max = temp;
			}
			if(limit == 1){
				printf("\nUnfortunately, the max limit to reserve a room has been reached.\nWill take you back to the main menu.\n");
				getch();
				user[*numUser].Max--; 
				(*numUser)--;
				bStop = 1;
			}
			(*numUser)++;
			getch();
			bStop = 1;							
		}	
	}while(!bStop);
}

/* reserveRoom2 is the second stage of reserving a room, it gets the user input about the 
				room details and the date details.
@param user - People User struct
@param numUser - amount of people currently on the database struct
Pre-condition: Does not hit an invalid or again
*/

void reserveRoom2(Person user, int *numUser)
{
	int bStop = 0;
	int again = 0;
	int j;
	int floornum = 0000;
	char combination[5];
	char combination1[5];
	char rName = 'G'; //roomname
	int userweek, userday, usertimeslot, userfloor, userroom, userparticipant;
	
	// initialize schedule
	system("cls");
	do{
		do{
			printf("Enter Week number (week 1, 2 or 3 only): \n");
			scanf("%d", &userweek);
			getchar();
			system("cls");
			if(userweek >= 1 && userweek <= 3){
				user[*numUser].Date.Week = userweek;
				printf("Enter Day of the week: ");
				printf("\n 1- Monday\n 2- Tuesday\n 3- Wednesday\n 4- Thursday\n 5- Friday\n 6- Saturday\n");
				scanf("%d", &userday);
				getchar();
				system("cls");
				if(userday >= 1 && userday <= 6){
					user[*numUser].Date.nDay.Day = userday;
					if(userday == 1 || userday == 2 || userday == 4 || userday == 5){
						printf("TimeSlot A (pick only from 1 to 6): ");
						printf("\n 1- 09:15 - 10:45\n 2- 11:00 - 12:30\n 3- 12:45 - 14:15\n 4- 14:30 - 16:00\n 5- 16:15 - 17:45\n 6- 18:00 - 19:00\n");
						scanf("%d", &usertimeslot);
						getchar();
						system("cls");
						user[*numUser].Date.nDay.nTime.Time1 = usertimeslot; 
						user[*numUser].Date.nDay.nTime.Time2 = 0;
						printf("Enter Floor (1st, 2nd or 3rd floor only): \n");	
						scanf("%d", &userfloor);
						getchar();
						system("cls");
						if(userfloor >= 1 && userfloor <= 3){
							user[*numUser].Date.nDay.nTime.nFloor.Floor = userfloor;
							printf("Enter the First 4 Room Numbers\n(First 5 rooms are Classrooms,\nNext 2 rooms are Auditoriums,\nNext 3 rooms are Seminar Rooms,\nLast 5 rooms are Laboratories):\n");
							if(userfloor == 1){
								floornum = 1100;
								for(j = 0; j < 15; j++){
									floornum+=0001;
									sprintf(combination, "%c%d", rName, floornum);
									printf("%s\n", combination);
									}
								scanf("%d", &userroom);
								getchar();
								system("cls");
								if(userroom <= 1100 || userroom > 1115){
									printf("Invalid Room Number\n");
									again = 1;	
								}
								else{
									sprintf(combination1, "%c%d", rName, userroom);
									printf("%s\n", combination1);
									strcpy(user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code, combination1);
									//printf("%s\n", user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code); //to be deleted
									if(userroom >= 1100 && userroom <= 1105){
										printf("How many partipants renting in this room? (limit is 30 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 30){
											printf("Invalid!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
										}
									}
									else if(userroom == 1106 || userroom == 1107){
										printf("How many partipants renting in this room? (limit is 50 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 50){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
												reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
												again = 1;
												bStop = 1;
										}
									}
									else if(userroom >= 1108 && userroom <= 1110){
										printf("How many partipants renting in this room? (limit is 10 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 10){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;	
										}
									}
									
									else{
										printf("How many partipants renting in this room? (limit is 15 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 15){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
										}
									}
								}
							}
							else if(userfloor == 2){
								floornum = 2100;
								for(j = 0; j < 15; j++){
									floornum+=0001;
									sprintf(combination, "%c%d", rName, floornum);
									printf("%s\n", combination); 
								}
								scanf("%d", &userroom);
								getchar();
								system("cls");
								if(userroom <= 2100 || userroom > 2115){
									printf("Invalid Room Number\n");
									again = 1;	
								}
								else{
									sprintf(combination1, "%c%d", rName, userroom);
									printf("%s\n", combination1);
									strcpy(user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code, combination1);
									//printf("%s\n", user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code); //to be deleted
									if(userroom >= 2100 && userroom <= 2105){
										printf("How many partipants renting in this room? (limit is 30 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 30){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
											}
									}
									else if(userroom == 2106 || userroom == 2107){
										printf("How many partipants renting in this room? (limit is 50 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 50){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;	
										}
									}
									else if(userroom >= 2108 && userroom <= 2110){
										printf("How many partipants renting in this room? (limit is 10 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 10){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
										}
									}
									
									else{
										printf("How many partipants renting in this room? (limit is 15 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 15){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
											}
										}
									}
							}
							else if(userfloor == 3){
								floornum = 3100;
								for(j = 0; j < 15; j++){
									floornum+=0001;
									sprintf(combination, "%c%d", rName, floornum);
									printf("%s\n", combination); 
								}
								scanf("%d", &userroom);
								getchar();
								system("cls");
								if(userroom <= 3100 || userroom > 3115){
									printf("Invalid Room Number\n");
									again = 1;	
								}
								else{
									sprintf(combination1, "%c%d", rName, userroom);
									printf("%s\n", combination1);
									strcpy(user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code, combination1);
									//printf("%s\n", user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code); //to be deleted
									if(userroom >= 3100 && userroom <= 3105){
										printf("How many partipants renting in this room? (limit is 30 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 30){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
										}
									}
									else if(userroom == 3106 || userroom == 3107){
										printf("How many partipants renting in this room? (limit is 50 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 50){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
										}
									}
									else if(userroom >= 3108 && userroom <= 3110){
										printf("How many partipants renting in this room? (limit is 10 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 10){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;	
										}
									}
									
									else{
										printf("How many partipants renting in this room? (limit is 15 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 15){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
											}
										}
									}
							}	
							else{
							printf("Invalid input. \n");
							again = 1;
							}
						}
						else{
							printf("Invalid input. \n");
							again = 1;
						}
					}
					
					else{
						printf("TimeSlot B (pick only from 1 to 3): ");
						printf("\n 1- 09:00 - 12:00\n 2- 13:00 - 16:00\n 3- 16:15 - 19:15\n");
						scanf("%d", &usertimeslot);
						getchar();
						system("cls");
						user[*numUser].Date.nDay.nTime.Time2 = usertimeslot;
						user[*numUser].Date.nDay.nTime.Time1 = 0;
						printf("Enter Floor (1st, 2nd or 3rd floor only): \n");	
						scanf("%d", &userfloor);
						getchar();
						system("cls");
						if(userfloor >= 1 && userfloor <= 3){
							user[*numUser].Date.nDay.nTime.nFloor.Floor = userfloor;
							printf("Enter the First 4 Room Numbers\n(First 5 rooms are Classrooms,\nNext 2 rooms are Auditoriums,\nNext 3 rooms are Seminar Rooms,\nLast 5 rooms are Laboratories):\n");
							if(userfloor == 1){
								floornum = 1100;
								for(j = 0; j < 15; j++){
									floornum+=0001;
									sprintf(combination, "%c%d", rName, floornum);
									printf("%s\n", combination);
									}
								scanf("%d", &userroom);
								getchar();
								system("cls");
								if(userroom <= 1100 || userroom > 1115){
									printf("Invalid Room Number\n");
									again = 1;	
								}
								else{
									sprintf(combination1, "%c%d", rName, userroom);
									printf("%s\n", combination1);
									strcpy(user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code, combination1);
									//printf("%s\n", user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code); //to be deleted
									if(userroom >= 1100 && userroom <= 1105){
										printf("How many partipants renting in this room? (limit is 30 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 30){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
										}
									}
									else if(userroom == 1106 || userroom == 1107){
										printf("How many partipants renting in this room? (limit is 50 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 50){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
										}
									}
									else if(userroom >= 1108 && userroom <= 1110){
										printf("How many partipants renting in this room? (limit is 10 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 10){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;	
										}
									}
									
									else{
										printf("How many partipants renting in this room? (limit is 15 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 15){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
										}
									}
								}
							}
							else if(userfloor == 2){
								floornum = 2100;
								for(j = 0; j < 15; j++){
									floornum+=0001;
									sprintf(combination, "%c%d", rName, floornum);
									printf("%s\n", combination); 
								}
								scanf("%d", &userroom);
								getchar();
								system("cls");
								if(userroom <= 2100 || userroom > 2115){
									printf("Invalid Room Number\n");
									again = 1;	
								}
								else{
									sprintf(combination1, "%c%d", rName, userroom);
									printf("%s\n", combination1);
									strcpy(user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code, combination1);
									//printf("%s\n", user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code); //to be deleted
									if(userroom >= 2100 && userroom <= 2105){
										printf("How many partipants renting in this room? (limit is 30 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 30){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;	
										}
									}
									else if(userroom == 2106 || userroom == 2107){
										printf("How many partipants renting in this room? (limit is 50 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 50){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
										}
									}
									else if(userroom >= 2108 && userroom <= 2110){
										printf("How many partipants renting in this room? (limit is 10 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 10){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;
										}
									}
									else{
										printf("How many partipants renting in this room? (limit is 15 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 15){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;	
										}
									}
								}
							}
							else if(userfloor == 3){
								floornum = 3100;
								for(j = 0; j < 15; j++){
									floornum+=0001;
									sprintf(combination, "%c%d", rName, floornum);
									printf("%s\n", combination); 
								}
								scanf("%d", &userroom);
								getchar();
								system("cls");
								if(userroom <= 3100 || userroom > 3115){
									printf("Invalid Room Number\n");
									again = 1;	
								}
								else{
									sprintf(combination1, "%c%d", rName, userroom);
									printf("%s\n", combination1);
									strcpy(user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code, combination1);
									//printf("%s\n", user[*numUser].Date.nDay.nTime.nFloor.nClassroom.Code); //to be deleted
									if(userroom >= 3100 && userroom <= 3105){
										printf("How many partipants renting in this room? (limit is 30 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 30){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;	
										}
									}
									else if(userroom == 3106 || userroom == 3107){
										printf("How many partipants renting in this room? (limit is 50 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 50){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;	
										}
									}
									else if(userroom >= 3108 && userroom <= 3110){
										printf("How many partipants renting in this room? (limit is 10 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 10){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;	
										}
									}
									else{
										printf("How many partipants renting in this room? (limit is 15 students)\n");
										scanf("%d", &userparticipant);
										getchar();
										system("cls");
										if(userparticipant <= 0 || userparticipant > 15){
											printf("Too many people!\n");
											getch();
											again = 1;
										}
										else{
											reserveRoom3(user, numUser, userparticipant, userweek, userday, usertimeslot, userfloor, combination1);
											again = 1;
											bStop = 1;	
										}
									}
								}
							}	
							else{
							printf("Invalid input. \n");
							again = 1;
							}
						}
					}
				}
		
				else{
					printf("Invalid input. \n");
					again = 1;
				} 
			}
		
			else{
				printf("Invalid input. \n");
				again = 1;
			}			
		
		}while(!again);
			
	}while(!bStop);
}

/* reserveRoom1 is the first stage of reserving a room, it gets the user input about the 
				user details, and if it is valid, moves to the second stage.
@param user - People User struct
@param numUser - amount of people currently on the database struct
Pre-condition: Does not hit an invalid or again
*/

void reserveRoom1(Person user, int *numUser)
{
	int bStop = 0;
	int again = 0;
	int reinput = 0;
	char Key, keyy;
	do{
    	system("cls");
        	do{
        	printf("Enter ID number: \n");
        	scanf("%d", &user[*numUser].IDnum);
        	getchar();
        	fflush(stdin);
        	printf("Enter First Name: \n");
        	fgets(user[*numUser].FLName.First, sizeof(user[*numUser].FLName.First), stdin);
        	user[*numUser].FLName.First[strlen(user[*numUser].FLName.First)-1] = '\0'; //No backspace
        	printf("Enter Last Name: \n");
        	fgets(user[*numUser].FLName.Last, sizeof(user[*numUser].FLName.Last), stdin);
        	user[*numUser].FLName.Last[strlen(user[*numUser].FLName.Last)-1] = '\0'; //No backspace
        	printf("Enter Program Initial: \n");
        	fgets(user[*numUser].Program, sizeof(user[*numUser].Program), stdin);
        	user[*numUser].Program[strlen(user[*numUser].Program)-1] = '\0'; //No backspace
        	printf("Enter Year: \n");
        	scanf("%d", &user[*numUser].Year);
        	getchar();
        	do
        	{
                printf("******************************************\n");
            	printf("Is all the above info correct? Press Y if Yes and N if No to restart... \n");
            	Key = getchar();
            	getchar();
            	if (Key == 'Y' || Key == 'y')
            	{
            		//user[*numUser].databaseNum = *numUser;
            		system("cls");
            		printf("Would you like to go back to the main page? Press Y if yes and any key to proceed... \n"); 
            		keyy = getchar();
            		getchar();
            		if (keyy == 'Y' || keyy == 'y')
            		{
            			again = 1;
            			bStop = 1; //TEMPORARY
            		}
            		else 
                    {
            			reserveRoom2(user, numUser);
            			reinput = 1;
            			again = 1;
            			bStop = 1;
            		}
            	}
            	else if (Key == 'N' || Key == 'n')
            	{
            		system("cls");
            		reinput = 1;
            	}
            	else
            	{
                    printf("Invalid input");
                }      
            } while(!reinput); 	
    	}while (!again);
	}while (!bStop);
}

/* display shows the user how many user there are currently in the database, it also shows
		   the current Database ID of the user in question
@param user - People User struct
@param numUser - amount of people currently on the database struct
Pre-condition: Does not hit an invalid or again
*/

void display(Person user, int numUser)
{
	int i = 0;
	char choice;
	int bStop = 0;
	int bStopper = 0;
	
	do {
		if (numUser == 0)
		{
			system("cls");
			printf("No users in the database found!\n");
			printf("\n");
			printf("Press a key to return...");
			getch();
			bStopper = 1;
		}
		else
		{
			do
			{
				system("cls");
				printf("No. of users in record: %d\n", numUser);
				printf("\n");
				printf("DatabaseNum: %03d\n", user[i].databaseNum);
				printf("UserID: %03d\n", user[i].IDnum);
				printf("First Name: %s\n", user[i].FLName.First);
				printf("Last Name: %s\n", user[i].FLName.Last);
				printf("Week: %d\n", user[i].Date.Week);
				printf("Day: %d\n", user[i].Date.nDay.Day);
				printf("Floor: %d\n", user[i].Date.nDay.nTime.nFloor.Floor);
				printf("Room: %s\n", user[i].Date.nDay.nTime.nFloor.nClassroom.Code);
				printf("\n");
				printf("[N]ext [P]revious [R]eturn");

				choice = getch();

				if (choice == 'n' || choice == 'N')
				{
					if (i < numUser - 1)
						i++;
				}
				else if (choice == 'p' || choice == 'P')
				{
					if (i > 0)
						i--;
				}
				else if (choice == 'r' || choice == 'R')
				{
					bStop = 1;
					bStopper = 1;
				}
			} while (!bStop);
		}
	} while (!bStopper);
}

/* EditUser3 is the final stage of editing an existing user's room, it validates whether the new
				room can be reserved or not. If it can be reserved, it is now the user's new room.
@param user - People User struct
@param numUser - amount of people currently on the database struct
@param i - the database ID of the user editing their room, used as a way to obtain the user's details 
		   and edit them appropriately
@param temptimeslot1 - temporary data for the user input of time slot
@param temptimeslot2 - temporary data for the user input time slot
@param tempuserfloor - temporary data for the user input of the level of the floor
@param userparticipant - temporary data for the user input of participants
@param combination1 - temporary data for the user input of classroom code
@param inctimeslot1 - temporary data for the user input time slot
@param inctimeslot2 - temporary data for the user input time slot
Pre-condition: Does not hit an invalid or again
*/

void EditUser3(Person user, int *numUser, int *i, int temptimeslot1, int temptimeslot2, int tempuserfloor, int userparticipant, char *combination1, int inctimeslot1, int inctimeslot2)
{
	int k, check = 0, bStop = 0;
	nString tempDesc;
	do{
		do{
			printf("Description for the purpose of reserving your room?\n");
			fgets(tempDesc, sizeof(tempDesc), stdin);
			tempDesc[strlen(tempDesc)-1] = '\0';
			if(tempDesc[0] == '\0'){
				printf("You can't have an empty description.\n");
				getch();
			}
		}while(tempDesc[0] == '\0');
		for(k = 0; k < *numUser; k++){
			if(user[k].Date.nDay.nTime.nFloor.Floor == tempuserfloor && strcmp(user[k].Date.nDay.nTime.nFloor.nClassroom.Code, combination1) == 0 && user[k].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved == 1){
				printf("%d\n", user[k].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved); 
				getch();
				printf("There has been a reservation made here.\n");
				getch();
				bStop = 1;
				check = 1;
			}
		}
		if(check == 1){
			user[*i].Date.nDay.nTime.Time1 = inctimeslot1;
			user[*i].Date.nDay.nTime.Time2 = inctimeslot2;
			bStop = 1;
		}					
		else{
			user[*i].Date.nDay.nTime.Time1 = temptimeslot1;
			user[*i].Date.nDay.nTime.Time2 = temptimeslot2;
			user[*i].Date.nDay.nTime.nFloor.Floor = tempuserfloor;
			strcpy(user[*i].Date.nDay.nTime.nFloor.nClassroom.Code, combination1);
			strcpy(user[*i].Date.nDay.nTime.nFloor.nClassroom.type.Desc, tempDesc);
			user[*i].Date.nDay.nTime.nFloor.nClassroom.type.participants = userparticipant;
			user[*i].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved = 1;
			printf("Reserved!\n");	
			getch();
			bStop = 1;							
		}	
	}while(!bStop);
}

/* EditUser2 is the second stage of editing an existing user's room, it gets the user's
			 new room information. 
@param user - People User struct
@param numUser - amount of people currently on the database struct
@param i - the database ID of the user editing their room, used as a way to obtain the user's details 
		   and edit them appropriately
Pre-condition: Does not hit an invalid or again
*/

void EditUser2(Person user, int *numUser, int *i)
{
	int j, temptimeslot1, temptimeslot2, tempuserfloor, tempuserroom, userparticipant, inctimeslot1, inctimeslot2, again = 0, bStop = 0;
	int floornum = 0000;
	char combination[5];
	char combination1[5];
	char rName = 'G';
	do{
		do{	
		if(user[*i].Date.nDay.Day == 1 || user[*i].Date.nDay.Day == 2 || user[*i].Date.nDay.Day == 4 || user[*i].Date.nDay.Day == 5){
			inctimeslot1 = user[*i].Date.nDay.nTime.Time1;
			inctimeslot2 = user[*i].Date.nDay.nTime.Time2;
			temptimeslot2 = user[*i].Date.nDay.nTime.Time2;
			printf("TimeSlot A (pick only from 1 to 6): ");
			printf("\n 1- 09:15 - 10:45\n 2- 11:00 - 12:30\n 3- 12:45 - 14:15\n 4- 14:30 - 16:00\n 5- 16:15 - 17:45\n 6- 18:00 - 19:00\n");
			scanf("%d", &temptimeslot1);
			printf("Enter Floor (1st, 2nd or 3rd floor only): \n");	
			scanf("%d", &tempuserfloor);
			getchar();
			system("cls");
			if(tempuserfloor >= 1 && tempuserfloor <= 3){
				printf("Enter the First 4 Room Numbers\n(First 5 rooms are Classrooms,\nNext 2 rooms are Auditoriums,\nNext 3 rooms are Seminar Rooms,\nLast 5 rooms are Laboratories):\n");
				if(tempuserfloor == 1){
					floornum = 1100;
					for(j = 0; j < 15; j++){
						floornum+=0001;
						sprintf(combination, "%c%d", rName, floornum);
						printf("%s\n", combination);
					}
					scanf("%d", &tempuserroom);
					getchar();
					system("cls");
					if(tempuserroom <= 1100 || tempuserroom > 1115){
						printf("Invalid Room Number\n");
						again = 1;	
					}
					else{
						sprintf(combination1, "%c%d", rName, tempuserroom);
						printf("%s\n", combination1);
						if(tempuserroom >= 1100 && tempuserroom <= 1105){
							printf("How many partipants renting in this room? (limit is 30 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 30){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
							
								EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}
						else if(tempuserroom == 1106 || tempuserroom == 1107){
							printf("How many partipants renting in this room? (limit is 50 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 50){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
								EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}
						else if(tempuserroom >= 1108 && tempuserroom <= 1110){
							printf("How many partipants renting in this room? (limit is 10 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 10){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
								EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}	
						else{
							printf("How many partipants renting in this room? (limit is 15 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 15){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
								EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;	
							}
						}
					}
				}
				else if(tempuserfloor == 2){
					floornum = 2100;
					for(j = 0; j < 15; j++){
						floornum+=0001;
						sprintf(combination, "%c%d", rName, floornum);
						printf("%s\n", combination);
					}
					scanf("%d", &tempuserroom);
					getchar();
					system("cls");
					if(tempuserroom <= 2100 || tempuserroom > 2115){
						printf("Invalid Room Number\n");
						again = 1;	
					}
					else{
						sprintf(combination1, "%c%d", rName, tempuserroom);
						printf("%s\n", combination1);
						if(tempuserroom >= 2100 && tempuserroom <= 2105){
							printf("How many partipants renting in this room? (limit is 30 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 30){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
								EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}
						else if(tempuserroom == 2106 || tempuserroom == 2107){
							printf("How many partipants renting in this room? (limit is 50 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 50){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
							EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}
						else if(tempuserroom >= 2108 && tempuserroom <= 2110){
							printf("How many partipants renting in this room? (limit is 10 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 10){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
								EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}	
						else{
							printf("How many partipants renting in this room? (limit is 15 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 15){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
								EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}
					}
				}
				else if(tempuserfloor == 3){
					floornum = 3100;
					for(j = 0; j < 15; j++){
						floornum+=0001;
						sprintf(combination, "%c%d", rName, floornum);
						printf("%s\n", combination);
					}
					scanf("%d", &tempuserroom);
					getchar();
					system("cls");
					if(tempuserroom <= 3100 || tempuserroom > 3115){
						printf("Invalid Room Number\n");
						again = 1;	
					}
					else{
						sprintf(combination1, "%c%d", rName, tempuserroom);
						printf("%s\n", combination1);
						if(tempuserroom >= 3100 && tempuserroom <= 3105){
							printf("How many partipants renting in this room? (limit is 30 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 30){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
								EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;	
							}
						}
						else if(tempuserroom == 3106 || tempuserroom == 3107){
							printf("How many partipants renting in this room? (limit is 50 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 50){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
							EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;	
							}
						}
						else if(tempuserroom >= 3108 && tempuserroom <= 3110){
							printf("How many partipants renting in this room? (limit is 10 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 10){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
								EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}	
						else{
							printf("How many partipants renting in this room? (limit is 15 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 15){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
								EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;	
							}
						}
					}
				}
					
				else{
					printf("Invalid input. \n");
					again = 1;
				}
			}	
		}
		else{
			inctimeslot1 = user[*i].Date.nDay.nTime.Time1;
			temptimeslot1 = user[*i].Date.nDay.nTime.Time1;
			inctimeslot2 = user[*i].Date.nDay.nTime.Time2;
			printf("TimeSlot B (pick only from 1 to 3): ");
			printf("\n 1- 09:00 - 12:00\n 2- 13:00 - 16:00\n 3- 16:15 - 19:15\n");
			scanf("%d", &temptimeslot2);
			printf("Enter Floor (1st, 2nd or 3rd floor only): \n");	
			scanf("%d", &tempuserfloor);
			getchar();
			system("cls");
			if(tempuserfloor >= 1 && tempuserfloor <= 3){
				printf("Enter the First 4 Room Numbers\n(First 5 rooms are Classrooms,\nNext 2 rooms are Auditoriums,\nNext 3 rooms are Seminar Rooms,\nLast 5 rooms are Laboratories):\n");
				if(tempuserfloor == 1){
					floornum = 1100;
					for(j = 0; j < 15; j++){
						floornum+=0001;
						sprintf(combination, "%c%d", rName, floornum);
						printf("%s\n", combination);
					}
					scanf("%d", &tempuserroom);
					getchar();
					system("cls");
					if(tempuserroom <= 1100 || tempuserroom > 1115){
						printf("Invalid Room Number\n");
						again = 1;	
					}
					else{
						sprintf(combination1, "%c%d", rName, tempuserroom);
						printf("%s\n", combination1);
						if(tempuserroom >= 1100 && tempuserroom <= 1105){
							printf("How many partipants renting in this room? (limit is 30 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 30){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
							
									EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}
						else if(tempuserroom == 1106 || tempuserroom == 1107){
							printf("How many partipants renting in this room? (limit is 50 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 50){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
									EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}
						else if(tempuserroom >= 1108 && tempuserroom <= 1110){
							printf("How many partipants renting in this room? (limit is 10 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 10){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
									EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}	
						else{
							printf("How many partipants renting in this room? (limit is 15 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 15){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
									EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;	
							}
						}
					}
				}
				else if(tempuserfloor == 2){
					floornum = 2100;
					for(j = 0; j < 15; j++){
						floornum+=0001;
						sprintf(combination, "%c%d", rName, floornum);
						printf("%s\n", combination);
					}
					scanf("%d", &tempuserroom);
					getchar();
					system("cls");
					if(tempuserroom <= 2100 || tempuserroom > 2115){
						printf("Invalid Room Number\n");
						again = 1;	
					}
					else{
						sprintf(combination1, "%c%d", rName, tempuserroom);
						printf("%s\n", combination1);
						if(tempuserroom >= 2100 && tempuserroom <= 2105){
							printf("How many partipants renting in this room? (limit is 30 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 30){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
									EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}
						else if(tempuserroom == 2106 || tempuserroom == 2107){
							printf("How many partipants renting in this room? (limit is 50 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 50){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
									EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}
						else if(tempuserroom >= 2108 && tempuserroom <= 2110){
							printf("How many partipants renting in this room? (limit is 10 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 10){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
								EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}	
						else{
							printf("How many partipants renting in this room? (limit is 15 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 15){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
									EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}
					}
				}
				else if(tempuserfloor == 3){
					floornum = 3100;
					for(j = 0; j < 15; j++){
						floornum+=0001;
						sprintf(combination, "%c%d", rName, floornum);
						printf("%s\n", combination);
					}
					scanf("%d", &tempuserroom);
					getchar();
					system("cls");
					if(tempuserroom <= 3100 || tempuserroom > 3115){
						printf("Invalid Room Number\n");
						again = 1;	
					}
					else{
						sprintf(combination1, "%c%d", rName, tempuserroom);
						printf("%s\n", combination1);
						if(tempuserroom >= 3100 && tempuserroom <= 3105){
							printf("How many partipants renting in this room? (limit is 30 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 30){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
									EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;	
							}
						}
						else if(tempuserroom == 3106 || tempuserroom == 3107){
							printf("How many partipants renting in this room? (limit is 50 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 50){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
									EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;	
							}
						}
						else if(tempuserroom >= 3108 && tempuserroom <= 3110){
							printf("How many partipants renting in this room? (limit is 10 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 10){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
									EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;
							}
						}	
						else{
							printf("How many partipants renting in this room? (limit is 15 students)\n");
							scanf("%d", &userparticipant);
							getchar();
							system("cls");
							if(userparticipant <= 0 || userparticipant > 15){
								printf("Too many people!\n");
								getch();
								again = 1;
							}
							else{
									EditUser3(user, numUser, i, temptimeslot1, temptimeslot2, tempuserfloor, userparticipant, combination1, inctimeslot1, inctimeslot2);
								again = 1;
								bStop = 1;	
							}
						}
					}
				}
				else{
					printf("Invalid input. \n");
					again = 1;
				}
			}	
			
			}
		}while(!again);
	}while(!bStop);
}

/* EditUser1 is the first stage of editing an existing user's room, it checks whether there
			 is an existing reservation. If there is, it is onto the second stage of editing
			 the user's new room. 
@param user - People User struct
@param numUser - amount of people currently on the database struct
Pre-condition: Does not hit an invalid or again
*/

void EditUser1(Person user, int *numUser)
{
	int i, tempID, key, found, bStop = 0, again = 0;
	do{
		do{
			found = 0;
			system("cls");
			printf("Enter your system ID number that you want to edit: \n");
			scanf("%d", &tempID);
			for(i = 0; i < *numUser; i++){
				if(user[i].databaseNum == tempID){
					found = 1;
				}
			}	
			
			if(found == 1){
				printf("Hello, %s, you will make changes to reservation room: %s, floor %d.\nYou can only make changes on the same day.\n", user[tempID].FLName.First, user[tempID].Date.nDay.nTime.nFloor.nClassroom.Code, user[tempID].Date.nDay.nTime.nFloor.Floor); //to be erased
				getch();
				EditUser2(user, numUser, &tempID);
				again = 1;
				bStop = 1;		
			}
			
			else{
					printf("There is no user reservation. Press E to exit and any key to try again...\n");
					key = getch();
					if(key == 'E' || key == 'e'){
						again = 1;
						bStop = 1;
					} 
					else{
						again = 1;	
					}
				}
		}while(!again);
	}while(!bStop);
}

/* cancelRoom is in charge of deleting the desired room reservation of a user. It shifts the
			  new database ID if an entry within the database structure is deleted.
@param user - People User struct
@param numUser - amount of people currently on the database struct
@param i - the database ID of the user deleting their room, used as a way to obtain the user's details 
		   and delete them appropriately
Pre-condition: Does not hit an invalid or again
*/

void cancelRoom(Person user, int *numUser, int i)
{
	int j, k;

    if (i < 0 || i >= *numUser)
    {
        printf("Invalid index!\n");
        return;
    }
    else
    {
    	for(k = 0; k < *numUser; k++){
    		if(user[i].IDnum == user[k].IDnum){
    			user[k].Max--; 
			}
		}
        // Clear the data for the canceled room
        user[i].databaseNum = 0;
        user[i].IDnum = 0;
        strcpy(user[i].FLName.First, "");
        strcpy(user[i].FLName.Last, "");
        strcpy(user[i].Program, "");
        user[i].Year = 0;
        user[i].Date.Week = 0;
        user[i].Date.nDay.Day = 0;
        user[i].Date.nDay.nTime.Time1 = 0;
        user[i].Date.nDay.nTime.Time2 = 0;
        user[i].Date.nDay.nTime.nFloor.Floor = 0;
        strcpy(user[i].Date.nDay.nTime.nFloor.nClassroom.Code, "");
        user[i].Date.nDay.nTime.nFloor.nClassroom.type.participants = 0;
        strcpy(user[i].Date.nDay.nTime.nFloor.nClassroom.type.Desc, "");
        user[i].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved = 0;
        user[i].Max = 0;

        // Shift the remaining entries in the array
        for (j = i + 1; j < *numUser; j++)
        {
            user[j - 1].databaseNum = user[j].databaseNum - 1;
            user[j - 1].IDnum = user[j].IDnum;
            strcpy(user[j - 1].FLName.First, user[j].FLName.First);
            strcpy(user[j - 1].FLName.Last, user[j].FLName.Last);
            strcpy(user[j - 1].Program, user[j].Program);
            user[j - 1].Year = user[j].Year;
            user[j - 1].Date.Week = user[j].Date.Week;
            user[j - 1].Date.nDay.Day = user[j].Date.nDay.Day;
            user[j - 1].Date.nDay.nTime.Time1 = user[j].Date.nDay.nTime.Time1;
            user[j - 1].Date.nDay.nTime.Time2 = user[j].Date.nDay.nTime.Time2;
            user[j - 1].Date.nDay.nTime.nFloor.Floor = user[j].Date.nDay.nTime.nFloor.Floor;
            strcpy(user[j - 1].Date.nDay.nTime.nFloor.nClassroom.Code, user[j].Date.nDay.nTime.nFloor.nClassroom.Code);
            user[j - 1].Date.nDay.nTime.nFloor.nClassroom.type.participants = user[j].Date.nDay.nTime.nFloor.nClassroom.type.participants;
            strcpy(user[j - 1].Date.nDay.nTime.nFloor.nClassroom.type.Desc, user[j].Date.nDay.nTime.nFloor.nClassroom.type.Desc);
            user[j - 1].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved = user[j].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved;
            user[j - 1].Max = user[j].Max;
        }
        // Clear the last entry (now duplicated after shifting)
        user[*numUser - 1].databaseNum = 0;
        user[*numUser - 1].IDnum = 0;
        strcpy(user[*numUser - 1].FLName.First, "");
        strcpy(user[*numUser - 1].FLName.Last, "");
        strcpy(user[*numUser - 1].Program, "");
        user[*numUser - 1].Year = 0;
        user[*numUser - 1].Date.Week = 0;
        user[*numUser - 1].Date.nDay.Day = 0;
        user[*numUser - 1].Date.nDay.nTime.Time1 = 0;
        user[*numUser - 1].Date.nDay.nTime.Time2 = 0;
        user[*numUser - 1].Date.nDay.nTime.nFloor.Floor = 0;
        strcpy(user[*numUser - 1].Date.nDay.nTime.nFloor.nClassroom.Code, "");
        user[*numUser - 1].Date.nDay.nTime.nFloor.nClassroom.type.participants = 0;
        strcpy(user[*numUser - 1].Date.nDay.nTime.nFloor.nClassroom.type.Desc, "");
        user[*numUser - 1].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved = 0;
        user[*numUser - 1].Max = 0;

        // Update the number of users
        (*numUser)--;
    }
}

/* SaveUserInfo produces a .txt file and saves the users' information in the file to store 
				the current record of the database. It updates appropriately. 
@param user - People User struct
@param numUser - amount of people currently on the database struct
Pre-condition: Does not hit an invalid or again
*/

void SaveUserInfo(Person user, int numUser)
{
	FILE *pFile;
	int i;
	
	pFile = fopen("Records.txt", "wt");
	
	if (pFile != NULL)
	{
		fprintf (pFile,"%d\n",numUser);
		
		for(i = 0; i < numUser; i++)
		{
			fprintf(pFile, "%d\n", user[i].databaseNum);
			fprintf(pFile, "%d\n", user[i].IDnum);
			fprintf(pFile, "%s\n", user[i].FLName.First);
			fprintf(pFile, "%s\n", user[i].FLName.Last);
			fprintf(pFile, "%s\n", user[i].Program);
			fprintf(pFile, "%d\n", user[i].Year);
			fprintf(pFile, "%d\n", user[i].Date.Week);
			fprintf(pFile, "%d\n", user[i].Date.nDay.Day);
			if(user[i].Date.nDay.nTime.Time1 != 0){
				fprintf(pFile, "%d\n", user[i].Date.nDay.nTime.Time1);
				fprintf(pFile, "%d\n", user[i].Date.nDay.nTime.Time2);
				fprintf(pFile, "%d\n", user[i].Date.nDay.nTime.nFloor.Floor);
				fprintf(pFile, "%s\n", user[i].Date.nDay.nTime.nFloor.nClassroom.Code);
				fprintf(pFile, "%d\n", user[i].Date.nDay.nTime.nFloor.nClassroom.type.participants);
				fprintf(pFile, "%s\n", user[i].Date.nDay.nTime.nFloor.nClassroom.type.Desc);
				fprintf(pFile, "%d\n", user[i].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved);
				fprintf(pFile, "%d\n", user[i].Max);	
			}
			else if(user[i].Date.nDay.nTime.Time2 != 0){
				fprintf(pFile, "%d\n", user[i].Date.nDay.nTime.Time1);
				fprintf(pFile, "%d\n", user[i].Date.nDay.nTime.Time2);
				fprintf(pFile, "%d\n", user[i].Date.nDay.nTime.nFloor.Floor);
				fprintf(pFile, "%s\n", user[i].Date.nDay.nTime.nFloor.nClassroom.Code);
				fprintf(pFile, "%d\n", user[i].Date.nDay.nTime.nFloor.nClassroom.type.participants);
				fprintf(pFile, "%s\n", user[i].Date.nDay.nTime.nFloor.nClassroom.type.Desc);
				fprintf(pFile, "%d\n", user[i].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved);
				fprintf(pFile, "%d\n", user[i].Max);
			}		
		}	
		fclose(pFile);
	}
	else 
		printf("Unable to generate the file. \n");
}

/* ReportInfo produces a .txt file and saves the users' information in a readable manner 
				in the file to store the currently reserved rooms. It updates appropriately. 
@param user - People User struct
@param numUser - amount of people currently on the database struct
Pre-condition: Does not hit an invalid or again
*/

void ReportInfo(Person user, int numUser)
{
	FILE *pFile;
	int i;
	
	pFile = fopen("UserReport.txt", "wt");
	
	if (pFile != NULL)
	{
		fprintf(pFile,"\t\tReport of Reserved and Unreserved Rooms\n");
		fprintf(pFile,"\t      Number of Users in The Reservation System: %d\n",numUser);
		fprintf(pFile, "Database Number\tFirst Name\tLast Name\tWeek Number\tDay Number\tClassroom Reserved\tParticipants\n");
		
		for(i = 0; i < numUser; i++)
		{
			fprintf(pFile, "%d\t", user[i].databaseNum);
			fprintf(pFile, "\t%s\t", user[i].FLName.First);
			fprintf(pFile, "\t%s\t", user[i].FLName.Last);
			fprintf(pFile, "\t%d\t", user[i].Date.Week);
			fprintf(pFile, "\t%d\t", user[i].Date.nDay.Day);
			fprintf(pFile, "\t%s\t\t", user[i].Date.nDay.nTime.nFloor.nClassroom.Code);
			fprintf(pFile, "\t%d\n", user[i].Date.nDay.nTime.nFloor.nClassroom.type.participants);
		}	
		fprintf(pFile,"Everything else is Unreserved.\n");
		fclose(pFile);
	}
	else 
		printf("Unable to generate the file. \n");
}

/* loadUserInfo reads the SaveUserInfo's .txt file to update the current users' information 
				to the program's data structure. It updates appropriately. 
@param user - People User struct
@param numUser - amount of people currently on the database struct
Pre-condition: Does not hit an invalid or again
*/

void loadUserInfo(Person user, int *numUser)
{
	FILE *pFile;
	nString strLine;
	int i;
	
	pFile = fopen("Records.txt","rt");
	
	if(pFile != NULL){
		
		fgets(strLine,sizeof(strLine),pFile);
		*numUser = atoi(strLine);
		
		for(i = 0; i < *numUser; i++){
			fgets(strLine,sizeof(strLine),pFile);
			sscanf(strLine, "%d", &user[i].databaseNum);
			
			fgets(strLine,sizeof(strLine),pFile);
			user[i].IDnum = atoi(strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			strLine[strlen(strLine)-1] = '\0';
			strcpy(user[i].FLName.First, strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			strLine[strlen(strLine)-1] = '\0';
			strcpy(user[i].FLName.Last, strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			strLine[strlen(strLine)-1] = '\0';
			strcpy(user[i].Program, strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			user[i].Year = atoi(strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			user[i].Date.Week = atoi(strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			user[i].Date.nDay.Day = atoi(strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			user[i].Date.nDay.nTime.Time1 = atoi(strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			user[i].Date.nDay.nTime.Time2 = atoi(strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			user[i].Date.nDay.nTime.nFloor.Floor = atoi(strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			strLine[strlen(strLine)-1] = '\0';
			strcpy(user[i].Date.nDay.nTime.nFloor.nClassroom.Code, strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			user[i].Date.nDay.nTime.nFloor.nClassroom.type.participants = atoi(strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			strLine[strlen(strLine)-1] = '\0';
			strcpy(user[i].Date.nDay.nTime.nFloor.nClassroom.type.Desc, strLine);
			
			fgets(strLine,sizeof(strLine),pFile);
			user[i].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved = atoi(strLine);
		
			fgets(strLine,sizeof(strLine),pFile);
			user[i].Max = atoi(strLine);
		}
		
		fclose(pFile);
	}
	else{
		*numUser = 0;
	}
}

/* initializeReservedSlot initializes all of the reserved flag and max reservation flags to 0.
@param user - People User struct
@param numUser - amount of people currently on the database struct
Pre-condition: Does not hit an invalid or again
*/

void initializeReservedSlot(Person user, int *numUser) {
    int i;
	for (i = 0; i < *numUser; i++) {
		user[i].Max = 0;
		user[i].Date.nDay.nTime.nFloor.nClassroom.type.reservation.isReserved = 0;
    }
}

int main()
{
	int bStop, bStopper = 0, found;
	char nChoice, nchoice;
	nString tempUN; //temporary username 
	int i, tempID;
	Person user; //people reservation
	int numUser = 0; //amt of users at the database

	initializeReservedSlot(user, &numUser);
	loadUserInfo(user, &numUser);
	
	do
	{
		system("cls");
		printf("******************************************\n");
		printf("Room Reservation in Gokongwei~!\n");
		printf("******************************************\n");
		printf("Select an option~\n");
		printf("[a] Reserve a Room\n");
		printf("[b] Edit your Reservation\n");
		printf("[c] Cancel your Reservation\n");
		printf("[d] Mark a Reservation as Completed\n");
		printf("[e] Know Your Current Database ID\n");
		printf("[x] Press any key to stop!\n");
		//nChoice = getchar();
		scanf(" %c", &nChoice);
		
		bStop = 0;
		
		if(nChoice == 'a' || nChoice == 'A'){
			reserveRoom1(user, &numUser);
		}
		
		else if(nChoice == 'b' || nChoice == 'B'){
			EditUser1(user, &numUser);
		}
		
		else if(nChoice == 'c' || nChoice == 'C'){
			do{
				do{
					found = 0;
					system("cls");
					printf("Enter your system ID number that you want to cancel: \n");
					scanf("%d", &tempID);
					for(i = 0; i < numUser; i++){
						if(user[i].databaseNum == tempID){
							found = 1;
						}
					}
				
					if(found == 1){
						printf("Hello, %s, you will cancel your reservation room.\n", user[tempID].FLName.First);
						getch();
						cancelRoom(user, &numUser, tempID);
						printf("The room is successfully cancelled.\n"); 
						getch();
						bStopper = 1;
						
					}
				
					else{
						printf("There is no user reservation. Press 'E' to exit...\n");  
						nchoice = getch();
						if(nchoice == 'e' || nchoice == 'E'){
							getch();
							found = 1;
							bStopper = 1;
						}
						
						else{
							getch();
							bStopper = 1;
						}
					}
				}while(!found);	
			}while(!bStopper);
		}
		
		else if(nChoice == 'd' || nChoice == 'D'){
			do{
				do{
					found = 0;
					system("cls");
					printf("Enter your system ID number that you want to mark as completed: \n");
					scanf("%d", &tempID);
					for(i = 0; i < numUser; i++){
						if(user[i].databaseNum == tempID){
							found = 1;
						}
					}
				
					if(found == 1){
						strcpy(tempUN, user[tempID].FLName.First);
						cancelRoom(user, &numUser, tempID);
						printf("Congratulations %s for successfully completing a room reservation!", tempUN); 
						getch();
						strcpy(tempUN, "");
						bStopper = 1;
						
					}
				
					else{
						printf("There is no user reservation. Press 'E' to exit...\n");  
						nchoice = getch();
						if(nchoice == 'e' || nchoice == 'E'){
							getch();
							found = 1;
							bStopper = 1;
						}
						
						else{
							getch();
							bStopper = 1;
						}
					}
				}while(!found);	
			}while(!bStopper);
		}
		
		else if(nChoice == 'e' || nChoice == 'E'){
			display(user, numUser);
		}
		
		else{
			bStop = 1;
		}
		
	}while(!bStop);
	SaveUserInfo(user, numUser);
	ReportInfo(user, numUser);
	return 0;
}