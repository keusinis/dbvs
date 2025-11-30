/* Processed by ecpg (18.1) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "main.pgc"
#include <stdio.h>
#include <stdlib.h>
#include <sqlca.h>

int get_int()
{
    int i;
    while(1)
    {
        if(scanf("%d", &i) == 1 && getchar() == '\n')
            return i;
        else 
        {
            printf("Wrong input! \n");
            while(getchar() != '\n')
                ;
        }
    }
}

void charToUpper(char* ch)
{
    if (*ch >= 'a' && *ch <= 'z') 
        *ch -= ('a' - 'A');
}

int checkin_choice ()
{   
    int choice;
    /* exec sql begin declare section */
         
         
         

         
         
    
#line 31 "main.pgc"
 long member_id ;
 
#line 32 "main.pgc"
 char name [ 255 ] ;
 
#line 33 "main.pgc"
 char surname [ 255 ] ;
 
#line 35 "main.pgc"
 char nameEntered [ 255 ] ;
 
#line 36 "main.pgc"
 char surnameEntered [ 255 ] ;
/* exec sql end declare section */
#line 37 "main.pgc"


    do
    {
        printf("\n0. Cancel...\n");
        printf("1. Search for Id by name and/or surname...\n");
        printf("2. Enter member Id...\n");
        printf("Select option: ");

        choice = get_int();

        switch (choice)
        {
            case 0:
                return 0;
            case 1:
                printf("Enter name (empty for any): ");
                fgets(nameEntered, sizeof(nameEntered), stdin);
                nameEntered[strcspn(nameEntered, "\n")] = '\0';

                printf("Enter surname (empty for any): ");
                fgets(surnameEntered, sizeof(surnameEntered), stdin);
                surnameEntered[strcspn(surnameEntered, "\n")] = '\0';

                printf("matches for: %s %s\n", nameEntered, surnameEntered);

                ECPGset_var( 0, ( surnameEntered ), __LINE__);\
 ECPGset_var( 1, ( surnameEntered ), __LINE__);\
 ECPGset_var( 2, ( nameEntered ), __LINE__);\
 ECPGset_var( 3, ( nameEntered ), __LINE__);\
 /* declare curs cursor for select member_id , name , surname from member where ( name = $1  or $2  = '' ) and ( surname = $3  or $4  = '' ) order by member_id */
#line 69 "main.pgc"

#line 69 "main.pgc"


                printf("Member_id | Name | Surname\n");

                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare curs cursor for select member_id , name , surname from member where ( name = $1  or $2  = '' ) and ( surname = $3  or $4  = '' ) order by member_id", 
	ECPGt_char,(nameEntered),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(nameEntered),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(surnameEntered),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(surnameEntered),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 73 "main.pgc"

                while ( 1 )
                {
                    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch curs", ECPGt_EOIT, 
	ECPGt_long,&(member_id),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(name),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(surname),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 76 "main.pgc"

                    if (SQLCODE == 100)
                        break;
                    else if (SQLCODE != 0)
                    {
                        printf("Error fetching data: %ld\n", SQLCODE);
                        break;
                    }
                    printf("%d %s %s\n", member_id, name, surname);
                }
                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs", ECPGt_EOIT, ECPGt_EORT);}
#line 86 "main.pgc"


                printf("\nEnter member_id (0 to cancel): ");
                return get_int();
                break;        
            case 2:
                /* declare curs1 cursor for select member_id , name , surname from member order by member_id */
#line 95 "main.pgc"

                printf("Member_id | Name | Surname\n");
                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare curs1 cursor for select member_id , name , surname from member order by member_id", ECPGt_EOIT, ECPGt_EORT);}
#line 97 "main.pgc"

                while ( 1 )
                {
                    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch curs1", ECPGt_EOIT, 
	ECPGt_long,&(member_id),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(name),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(surname),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 100 "main.pgc"

                    if (SQLCODE == 100)
                        break;
                    else if (SQLCODE != 0)
                    {
                        printf("Error fetching data: %ld\n", SQLCODE);
                        break;
                    }
                    printf("%d %s %s\n", member_id, name, surname);
                }
                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs1", ECPGt_EOIT, ECPGt_EORT);}
#line 110 "main.pgc"


                printf("\nEnter member_id (0 to cancel): ");
                return get_int();
                break;
            default:
                printf("Invalid choice. Please enter a number between 0 and 2\n");
        }
    } while (1);
}

short membership_update()
{
    /* exec sql begin declare section */
         
         
         
         
    
#line 124 "main.pgc"
 long member_id_param ;
 
#line 125 "main.pgc"
 long membership_id_param ;
 
#line 126 "main.pgc"
 char bought_on_param [ 11 ] ;
 
#line 127 "main.pgc"
 long duration_in_months_param ;
/* exec sql end declare section */
#line 128 "main.pgc"


    char inbuffer[40];
    short ok = 1;

    /* declare curs3 cursor for select member_id , membership_id , bought_on , duration_in_months from member_membership */
#line 135 "main.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare curs3 cursor for select member_id , membership_id , bought_on , duration_in_months from member_membership", ECPGt_EOIT, ECPGt_EORT);}
#line 137 "main.pgc"


    while (1)
    {
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch curs3", ECPGt_EOIT, 
	ECPGt_long,&(member_id_param),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(membership_id_param),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(bought_on_param),(long)11,(long)1,(11)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(duration_in_months_param),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 141 "main.pgc"

        if (SQLCODE == 100)
            goto ending;
        else if (SQLCODE != 0)
        {   
            goto error;
        }
        printf("\nmember_id: %d\n", member_id_param);
        printf("membership_id_param: %d\n", membership_id_param);
        printf("bought_on: %s\n", bought_on_param);
        printf("duration_in_months: %d\n", duration_in_months_param);

        action:
        printf("Choose: N, D, U, F, C\n");
        scanf("%s", inbuffer);

        charToUpper(&inbuffer[0]);
        switch (inbuffer[0])
        {
        case 'N':
            break;
        case 'D':
            { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "delete from member_membership where current of curs3", ECPGt_EOIT, ECPGt_EORT);}
#line 164 "main.pgc"

            break;
        case 'U':
            printf("Enter new values:\n");
            printf("Enter membership_id_param: (1-8)");
            scanf("%d", &membership_id_param);

            { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update member_membership set membership_id = $1  where current of curs3", 
	ECPGt_long,&(membership_id_param),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 173 "main.pgc"

            break;
        case 'F':
            goto ending;
        case 'C':
            ok = 0;
            goto ending;
        default:
            goto action;
        }
    }

    error:
        printf("SQL Error %ld: %s\n", sqlca.sqlcode, sqlca.sqlerrm.sqlerrmc);
        ok = 0;

    ending:
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs3", ECPGt_EOIT, ECPGt_EORT);}
#line 190 "main.pgc"


    if (ok)
    {
        { ECPGtrans(__LINE__, NULL, "commit");}
#line 194 "main.pgc"

        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "refresh materialized view member_hours_summary", ECPGt_EOIT, ECPGt_EORT);}
#line 195 "main.pgc"

    }
    else
        { ECPGtrans(__LINE__, NULL, "rollback");}
#line 198 "main.pgc"


    return ok;
}

int addNewMember(const char* name, const char* surname, const char* dob,
                 const char* city, const char* street, int house, int apartment)
{
    /* exec sql begin declare section */
         
         
         
         
         
         
         
         
    
#line 207 "main.pgc"
 char nameParam [ 255 ] ;
 
#line 208 "main.pgc"
 char surnameParam [ 255 ] ;
 
#line 209 "main.pgc"
 char dobParam [ 11 ] ;
 
#line 210 "main.pgc"
 char cityParam [ 255 ] ;
 
#line 211 "main.pgc"
 char streetParam [ 255 ] ;
 
#line 212 "main.pgc"
 long houseParam ;
 
#line 213 "main.pgc"
 long apartmentParam ;
 
#line 214 "main.pgc"
 long addressIdParam ;
/* exec sql end declare section */
#line 215 "main.pgc"


    strcpy(nameParam, name);
    strcpy(surnameParam, surname);
    strcpy(dobParam, dob);
    strcpy(cityParam, city);
    strcpy(streetParam, street);
    houseParam = house;
    apartmentParam = apartment;

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select address_id from address where city = $1  and street = $2  and house = $3  and apartment = $4 ", 
	ECPGt_char,(cityParam),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(streetParam),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(houseParam),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(apartmentParam),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_long,&(addressIdParam),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 228 "main.pgc"

    
    if(SQLCODE < 0)
    {
        printf("Error fetching address: %ld\n", SQLCODE);
        return -1;
    }
    if(SQLCODE == 100)
    {
        printf("Inserting new address\n");
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into address ( city , street , house , apartment ) values ( $1  , $2  , $3  , $4  ) returning address_id", 
	ECPGt_char,(cityParam),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(streetParam),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(houseParam),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(apartmentParam),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_long,&(addressIdParam),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 240 "main.pgc"


        if (SQLCODE != 0)
        {
            printf("Error inserting address: %ld\n", SQLCODE);
            return -1;
        }
    }
    else
    {
        printf("Using existing address\n");
    }

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into member ( name , surname , dob , address_id ) values ( $1  , $2  , TO_DATE ( $3  , 'YYYY-MM-DD' ) , $4  )", 
	ECPGt_char,(nameParam),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(surnameParam),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(dobParam),(long)11,(long)1,(11)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(addressIdParam),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 254 "main.pgc"


    if (SQLCODE != 0)
    {
        printf("Error inserting member: %ld\n", SQLCODE);

        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "delete from address where address_id = $1 ", 
	ECPGt_long,&(addressIdParam),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 260 "main.pgc"

        return -1;
    }

    { ECPGtrans(__LINE__, NULL, "commit");}
#line 264 "main.pgc"


    return 0;
}

void readMemberInfoFromFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    char name[255];
    char surname[255];
    char dob[11];
    char city[255];
    char street[255];
    int house;
    int apartment;

    while (fscanf(file, "%s %s %s %s %s %d %d", name, surname, dob, city, street, &house, &apartment) == 7)
    {
        int result = addNewMember(name, surname, dob, city, street, house, apartment);

        if (result == 0)
            printf("Member added successfully!\n");
        else
            printf("Failed to add member %s %s.\n", name, surname);
        
        name[0] = '\0';
        surname[0] = '\0';
        dob[0] = '\0';
        city[0] = '\0';
        street[0] = '\0';
        house = 0;
        apartment = 0;
    }

    fclose(file);
}

int main()
{
    /* exec sql begin declare section */
         
         
         
    
#line 310 "main.pgc"
 char DB_NAME [ 50 ] ;
 
#line 311 "main.pgc"
 char DB_USER [ 50 ] ;
 
#line 312 "main.pgc"
 char DB_PASS [ 50 ] ;
/* exec sql end declare section */
#line 313 "main.pgc"


    char *env_name = getenv("DB_NAME");
    char *env_user = getenv("DB_USER");
    char *env_pass = getenv("DB_PASS");

    if (!env_name || !env_user || !env_pass)
    {
        fprintf(stderr, "Error: DB_NAME, DB_USER or DB_PASS environment variable not set.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(DB_NAME, env_name, sizeof(DB_NAME)-1);
    DB_NAME[sizeof(DB_NAME)-1] = '\0';

    strncpy(DB_USER, env_user, sizeof(DB_USER)-1);
    DB_USER[sizeof(DB_USER)-1] = '\0';

    strncpy(DB_PASS, env_pass, sizeof(DB_PASS)-1);
    DB_PASS[sizeof(DB_PASS)-1] = '\0';

    { ECPGconnect(__LINE__, 0, DB_NAME , DB_USER , DB_PASS , NULL, 0); }
#line 334 "main.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "refresh materialized view member_hours_summary", ECPGt_EOIT, ECPGt_EORT);}
#line 335 "main.pgc"


    int choice;
    if (sqlca.sqlcode < 0)
    {
        fprintf(stderr, "Database connection failed: %s\n", sqlca.sqlerrm.sqlerrmc);
        exit(EXIT_FAILURE);
    }

    do {
        printf("0. Exit\n");
        printf("1. Check-in member..\n");
        printf("2. Check-out member...\n");
        printf("3. Add new member (file \"member.txt\"):\n");
        printf("4. Edit member memberships...\n");

        printf("Select option: ");
        choice = get_int();

        switch (choice)
        {
            case 0: // Exit
                printf("Exiting the program. Goodbye!\n");
                break;
            case 1: // New check-in                
                /* exec sql begin declare section */
                     
                     
                
#line 361 "main.pgc"
 long mem_id ;
 
#line 362 "main.pgc"
 char gym_pool [ 10 ] ;
/* exec sql end declare section */
#line 363 "main.pgc"

                mem_id = checkin_choice();
                if(mem_id > 0)
                {
                    printf("1. Gym\n2. Pool\nChoice: ");
                    int type = get_int();
                    switch(type)
                    {
                        case 1:
                            strcpy(gym_pool,"gym");
                            break;
                        case 2:
                            strcpy(gym_pool,"pool");
                            break;
                        default:
                            strcpy(gym_pool,"empty");
                            break;
                        
                    }
                    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into checkin ( member_id , location_id , gym_or_pool ) values ( $1  , 1 , $2  )", 
	ECPGt_long,&(mem_id),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(gym_pool),(long)10,(long)1,(10)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 383 "main.pgc"

                    if (SQLCODE != 0)
                    {
                        printf("Error checking-in: %ld\n", SQLCODE);
                        break;
                    }
                    { ECPGtrans(__LINE__, NULL, "commit");}
#line 389 "main.pgc"

                }
                break;
            case 2: // Check-out
                    /* exec sql begin declare section */
                         
                         
                    
#line 394 "main.pgc"
 char name [ 255 ] ;
 
#line 395 "main.pgc"
 char surname [ 255 ] ;
/* exec sql end declare section */
#line 396 "main.pgc"


                    /* declare curs2 cursor for select member_id , name , surname from currently_checked_in_members order by member_id */
#line 401 "main.pgc"


                    printf("Currently checked-in members:\nMember_id | Name | Surname\n");

                    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare curs2 cursor for select member_id , name , surname from currently_checked_in_members order by member_id", ECPGt_EOIT, ECPGt_EORT);}
#line 405 "main.pgc"

                    while (1) {
                        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch curs2", ECPGt_EOIT, 
	ECPGt_long,&(mem_id),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(name),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(surname),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 407 "main.pgc"

                        if (SQLCODE == 100) // No more rows
                            break;
                        else if (SQLCODE != 0) {
                            printf("Error fetching data: %ld\n", SQLCODE);
                            break;
                        }
                        printf("%d %s %s\n", mem_id, name, surname);
                    }
                    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs2", ECPGt_EOIT, ECPGt_EORT);}
#line 416 "main.pgc"

                    printf("\nEnter member_id (0 to cancel): ");
                    mem_id = get_int();
                    
                    if(mem_id > 0)
                    {
                        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update checkin set checkout_time = current_timestamp where member_id = $1 ", 
	ECPGt_long,&(mem_id),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 424 "main.pgc"

                        if (SQLCODE != 0) 
                        {
                            printf("Error fetching data: %ld\n", SQLCODE);
                            break;
                        }
                    { ECPGtrans(__LINE__, NULL, "commit");}
#line 430 "main.pgc"

                    }
                break;
                
            case 3: // Add new member
                printf("Add new member(s) (info in file \"member.txt\"):\n");
                    const char* filename = "member.txt";
                    readMemberInfoFromFile(filename);
                break;            
            case 4: // Edit member membership
                short result = membership_update();

                if(result)
                    printf("Changes applied successfully\n");
                else
                    printf("Cancelled\n");

                break;
            default:
                printf("Invalid choice. Please enter a number between 0 and 4\n");
        }
        printf("\n");

    } while (choice != 0);

    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 455 "main.pgc"

    return 0;
}
