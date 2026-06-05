#define MAX_STUDENTS 100
#define FILENAME "records.csv"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

void write_headers() {
    FILE *fptr = fopen(FILENAME, "w");   
    if (!fptr) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fptr,
            "Name,Roll_No,Class,Phone_no,E-Mail,Eng,Phy,Chem,Maths,C.S,Percent\n");

    fclose(fptr);
}

typedef struct basic_layout{
    char name[20];
    int roll_no;
    char class[10];
    char phone_no[15];
    char email[30];
    int marks[5];
    float percentage;}info;

int login() {
    char password[20];
    char correct_password[20] = "admin123";

    printf("Enter admin password: ");
    scanf("%s", password);

    if (strcmp(password, correct_password) == 0) {
        printf("Access granted.\n");
        return 1;
    } else {
        printf("Wrong password! Access denied.\n");
        return 0;
    }
}

int parse_line(char *line, info *s) {
    return sscanf(line,
        " %19[^,],%d,%9[^,],%14[^,],%29[^,],%d,%d,%d,%d,%d,%f",
        s->name, &s->roll_no, s->class, s->phone_no, s->email,
        &s->marks[0], &s->marks[1], &s->marks[2],
        &s->marks[3], &s->marks[4], &s->percentage);
}

void save_exit(){
    exit(0);
}

void save_record(info s) {
    FILE *fptr = fopen(FILENAME, "a");  
    if (!fptr) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fptr, "%s,%d,%s,%s,%s,%d,%d,%d,%d,%d,%.2f\n",
            s.name, s.roll_no, s.class, s.phone_no, s.email,
            s.marks[0], s.marks[1], s.marks[2], s.marks[3], s.marks[4],
            s.percentage);

    fclose(fptr);
}

void new_entry(info students[], int *student_count){
    char subjects[5][20]={"English","Physics","Chemistry","Maths","Computer Science"};
    int a;
    printf("How many students' data you would like to enter:");
    scanf("%d",&a);
    
    for(int i=0;i<a && *student_count<MAX_STUDENTS;i++){
        int idx=*student_count;
        int total_marks=0;
        printf("Enter the name:");
        scanf(" %[^\n]",students[idx].name);
        
        printf("Enter the roll no:");
        scanf("%d",&students[idx].roll_no);

        FILE *fptr = fopen(FILENAME, "r");
        if (!fptr) {
            printf("Error opening file!\n");
            return;}

        int roll;
        char line[512];

        while (fgets(line, sizeof(line), fptr)) {
            info temp;
            if (parse_line(line, &temp) != 11) continue;
            
            if(temp.roll_no==students[idx].roll_no){
                printf("Roll number already exists.\n");
                fclose(fptr);
                return;}}
        fclose(fptr);
        
        printf("Enter the class:");
        scanf(" %[^\n]",students[idx].class);
        
        printf("Enter the phone number:");
        scanf(" %[^\n]",students[idx].phone_no);
        
        printf("Enter the e-mail:");
        scanf(" %[^\n]",students[idx].email);
        
        for(int j=0;j<5;j++){
            printf("Enter the marks of %s:",subjects[j]);
            scanf("%d",&students[idx].marks[j]);
            total_marks+=students[idx].marks[j];
        }
        printf("\n");
        printf("Record added successfully\n");
        
        students[idx].percentage=((float) total_marks/500)*100;
        (*student_count)++;
        save_record(students[idx]);}}

void display_record() {
    FILE *fptr = fopen(FILENAME, "r");
    if (!fptr) {
        printf("Error opening file!\n");
        return;
    }
    char line[512];
    // fgets(line, sizeof(line), fptr);
    printf("\n%-15s %-8s %-8s %-12s %-25s %-6s %-6s %-6s %-6s %-6s %-8s\n",
           "Name", "Roll_No", "Class", "Phone_no", "E-Mail",
           "Eng", "Phy", "Chem", "Math", "C.S", "Percent");

    printf("-------------------------------------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fptr)) {
        info temp;
        if (parse_line(line, &temp) != 11) continue;

        printf("%-15s %-8d %-8s %-12s %-25s %-6d %-6d %-6d %-6d %-6d %-8.2f\n",
               temp.name, temp.roll_no, temp.class, temp.phone_no, temp.email,
               temp.marks[0], temp.marks[1], temp.marks[2],
               temp.marks[3], temp.marks[4], temp.percentage);
    }

    fclose(fptr);}

void stu_by_roll() {
    FILE *fptr = fopen(FILENAME, "r");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int roll;
    printf("Enter the Roll number to be searched: ");
    scanf("%d", &roll);
    

    char line[512];
    int found = 0;
    // fgets(line, sizeof(line), fptr);

    while (fgets(line, sizeof(line), fptr)) {
        info temp;
        if (parse_line(line, &temp) != 11) continue;

        if (temp.roll_no == roll) {
            found = 1;

            printf("\n%-15s %-8s %-8s %-12s %-25s %-7s %-7s %-9s %-7s %-7s %-10s\n",
                   "Name", "Roll_No", "Class", "Phone_no", "E-Mail",
                   "Eng", "Phy", "Chem", "Maths", "C.S", "Percent");

            printf("%-15s %-8d %-8s %-12s %-25s %-7d %-7d %-9d %-7d %-7d %-10.2f\n",
                   temp.name, temp.roll_no, temp.class, temp.phone_no,
                   temp.email, temp.marks[0], temp.marks[1], temp.marks[2],
                   temp.marks[3], temp.marks[4], temp.percentage);
            break;
        }
    }

    if (!found)
        printf("No such record found.\n");

    fclose(fptr);
}

void stu_by_name(){
    int found=0;
    char search[20];
    printf("Enter the name to be searched:");
    scanf(" %[^\n]",search);
    FILE *fptr=fopen(FILENAME,"r");
    if(!fptr){
        printf("Error opening file\n");
        return;
    }
    char line[512];
    // fgets(line,sizeof(line),fptr);
    while(fgets(line,sizeof(line),fptr)){
        info temp;
        if (parse_line(line, &temp) != 11) continue;
    
        if(strcmp(temp.name,search)==0){
            found=1;
            printf("\n%-15s %-8s %-8s %-12s %-25s %-7s %-7s %-9s %-7s %-7s %-10s\n",
                   "Name", "Roll_No", "Class", "Phone_no", "E-Mail",
                   "Eng", "Phy", "Chem", "Maths", "C.S", "Percent");

            printf("%-15s %-8d %-8s %-12s %-25s %-7d %-7d %-9d %-7d %-7d %-10.2f\n",
                   temp.name, temp.roll_no, temp.class, temp.phone_no,
                   temp.email, temp.marks[0], temp.marks[1], temp.marks[2],
                   temp.marks[3], temp.marks[4], temp.percentage);
            break;}}
    if(found==0) printf("No such record found\n");
    fclose(fptr);}

void parti_per(){
    int w,found=0;
    printf("Enter the roll no. whose percentage you want:");
    scanf("%d",&w);
    FILE *fptr;
    fptr=fopen(FILENAME,"r");
    if(!fptr){
        printf("Error opening file\n");
        return;
    }
    char line[512];
    // fgets(line,sizeof(line),fptr);
    while(fgets(line,sizeof(line),fptr)){
        info temp;
        if (parse_line(line, &temp) != 11) continue;

        if(temp.roll_no==w){
            found=1;
            printf("The percentage of roll number %d is %.2f",w,temp.percentage);
            break;
        }
    }
    if(found==0) printf("No such record found");
    fclose(fptr);
}

void class_topper(){
    FILE *fptr;
    info temp;
    float a=0.0;
    fptr=fopen(FILENAME,"r");
    if(!fptr){
        printf("Error opening the file");
        return;
}
    char line[512];
    // fgets(line,sizeof(line),fptr);
    while(fgets(line,sizeof(line),fptr)){
        if (parse_line(line, &temp) != 11) continue;

        if(temp.percentage>a){
            a=temp.percentage;}}
    rewind(fptr);
    while(fgets(line,sizeof(line),fptr)){
        if (parse_line(line, &temp) != 11) continue;

        if(temp.percentage==a) printf("%s is the overall topper of the class with %.2f\n",temp.name,temp.percentage);}
    if (a == 0.0f) {
    printf("No valid records found\n");
    fclose(fptr);
    return;
}}

void subject_topper(){
    info temp;
    FILE *fptr=fopen(FILENAME,"r");
    char subject[20];
    printf("Enter the subject whose topper you wanna know:");
    scanf(" %[^\n]",subject);
    if(!fptr){
        printf("Error opening the file");
        return;
    }
    char line[512];
    // fgets(line,sizeof(line),fptr);
    int marks=0;

    while(fgets(line,sizeof(line),fptr)){
        if (parse_line(line, &temp) != 11) continue;

        if(strcmp(subject,"english")==0 || strcmp(subject,"ENGLISH")==0){
            if(temp.marks[0]>marks){
            marks=temp.marks[0];
       }}
        
        else if(strcmp(subject,"physics")==0 || strcmp(subject,"PHYSICS")==0){
            if(temp.marks[1]>marks){
            marks=temp.marks[1];
          }}

        else if(strcmp(subject,"chemistry")==0 || strcmp(subject,"CHEMISTRY")==0){
            if(temp.marks[2]>marks){
            marks=temp.marks[2];
           }}
        
        else if(strcmp(subject,"maths")==0 || strcmp(subject,"MATHS")==0){
            if(temp.marks[3]>marks){
            marks=temp.marks[3];}}
        
        else if(strcmp(subject,"C.S")==0 || strcmp(subject,"c.s")==0){
            if(temp.marks[4]>marks){
            marks=temp.marks[4];
           }}
        else {printf("Invalid input");
            return;}}
    rewind(fptr);
    
    while(fgets(line,sizeof(line),fptr)){
        if (parse_line(line, &temp) != 11) continue;
        
        if(strcmp(subject,"ENGLISH")==0 || strcmp(subject,"english")==0){
            if(temp.marks[0]==marks){
                printf("The subject topper of %s is %s with %d marks.\n",subject,temp.name,marks);
            }
        }
        else if(strcmp(subject,"PHYSICS")==0 || strcmp(subject,"physics")==0){
            if(temp.marks[1]==marks){
                printf("The subject topper of %s is %s with %d marks.\n",subject,temp.name,marks);
            }
        }
        else if(strcmp(subject,"CHEMISTRY")==0 || strcmp(subject,"chemistry")==0){
            if(temp.marks[2]==marks){
                printf("The subject topper of %s is %s with %d marks.\n",subject,temp.name,marks);
            }
        }
        else if(strcmp(subject,"MATHS")==0 || strcmp(subject,"maths")==0){
            if(temp.marks[3]==marks){
                printf("The subject topper of %s is %s with %d marks.\n",subject,temp.name,marks);
            }
        }
        if(strcmp(subject,"C.S")==0 || strcmp(subject,"c.s")==0){
            if(temp.marks[4]==marks){
                printf("The subject topper of %s is %s with %d marks.\n",subject,temp.name,marks);
            }
        }
    
    }
    
    fclose(fptr);
}

void needy(){
    bool flag=false;
    FILE *fptr;
    info temp;
    fptr=fopen(FILENAME,"r");
    if(!fptr){
        printf("Error opening the file");
        return;
}
    char line[512];
    // fgets(line,sizeof(line),fptr);
    while(fgets(line,sizeof(line),fptr)){
        if (parse_line(line, &temp) != 11) continue;

        if(temp.percentage<50.00){
            flag=true;
            printf("%s requires guidance as his/her percentage is: %.2f\n",temp.name,temp.percentage);
        }}
    if(flag==false) printf("All students have percentage higher than 50");
    fclose(fptr);
}

void update(){
    FILE *fptr = fopen(FILENAME, "r");
    if (!fptr) {
        printf("Error opening file!\n");
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (!temp) {
        printf("Error creating temp file!\n");
        fclose(fptr);
        return;
    }

    int target_roll, found = 0;
    printf("Enter the roll number to update: ");
    scanf("%d", &target_roll);

    char line[512];
    if (fgets(line, sizeof(line), fptr) != NULL) {
        fputs(line, temp);
    }

    while (fgets(line, sizeof(line), fptr)) {
        info s;
        if (parse_line(line, &s) != 11) continue;

        if (s.roll_no == target_roll) {
            found = 1;
            printf("\nCurrent record:\n");
            printf("%-15s %-8d %-8s %-12s %-25s %3d %3d %3d %3d %3d  %6.2f\n",
                   s.name, s.roll_no, s.class, s.phone_no, s.email,
                   s.marks[0], s.marks[1], s.marks[2],
                   s.marks[3], s.marks[4], s.percentage);

            printf("\nEnter NEW details (press enter values again):\n");

            printf("Name: ");
            scanf(" %[^\n]", s.name);
            
            printf("Roll number:");
            scanf("%d",&s.roll_no);

            printf("Class: ");
            scanf(" %[^\n]", s.class);

            printf("Phone number: ");
            scanf(" %[^\n]", s.phone_no);

            printf("E-mail: ");
            scanf(" %[^\n]", s.email);

            int total = 0;
            char subjects[5][20] = {
                "English","Physics","Chemistry","Maths","Computer Science"
            };
            for (int i = 0; i < 5; i++) {
                printf("Marks in %s: ", subjects[i]);
                scanf("%d", &s.marks[i]);
                total += s.marks[i];
            }
            s.percentage = ((float)total / 500)*100;
            fprintf(temp, "%s,%d,%s,%s,%s,%d,%d,%d,%d,%d,%.2f\n",
                    s.name, s.roll_no, s.class, s.phone_no, s.email,
                    s.marks[0], s.marks[1], s.marks[2],
                    s.marks[3], s.marks[4], s.percentage);
        } else {
            fputs(line, temp);
        }
    }

    fclose(fptr);
    fclose(temp);

    if (!found) {
        printf("No record with roll %d found.\n", target_roll);
        remove("temp.csv");
    } else {
        remove(FILENAME);  
        rename("temp.csv", FILENAME); 
        printf("Record updated successfully.\n");
    }
}

void delete_record(){
    FILE *fptr = fopen(FILENAME, "r");
    if (!fptr) {
        printf("Error opening file!\n");
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (!temp) {
        printf("Error creating temp file!\n");
        fclose(fptr);
        return;
    }

    int target_roll, found = 0;
    printf("Enter the roll number to delete: ");
    scanf("%d", &target_roll);

    char line[512];
    if (fgets(line, sizeof(line), fptr) != NULL) {
        fputs(line, temp);
    }

    while (fgets(line, sizeof(line), fptr)) {
        info s;
        if (parse_line(line, &s) != 11) continue;

        if (s.roll_no == target_roll) {
            found = 1;
            continue;}
        
        fputs(line,temp);}
    
    fclose(fptr);
    fclose(temp);

    if (!found) {
        printf("No record with roll %d found.\n", target_roll);
        remove("temp.csv");
    } else {
        remove(FILENAME);  
        rename("temp.csv", FILENAME); 
        printf("Record deleted successfully.\n");
    }
}

void mean_marks(){
    info temp;
    FILE *fptr;
    int count=0;
    int mean_marks_eng=0;
    int mean_marks_phy=0;
    int mean_marks_chem=0;
    int mean_marks_math=0;
    int mean_marks_cs=0;
    fptr=fopen(FILENAME,"r");
    char line[512];
    if (!fptr) {
    printf("Error opening file\n");
    return;}
    //fgets(line,sizeof(line),fptr)
    while(fgets(line,sizeof(line),fptr)){
        if (parse_line(line, &temp) != 11) continue;
        mean_marks_eng+=temp.marks[0];
        mean_marks_phy+=temp.marks[1];
        mean_marks_chem+=temp.marks[2];
        mean_marks_math+=temp.marks[3];
        mean_marks_cs+=temp.marks[4];
        count++;}
    if (count == 0) {
        printf("No valid student records found.\n");
        fclose(fptr);
        return;
    }
    printf("The average marks of English are: %.2f\n",(float)mean_marks_eng/(float)count);
    printf("The average marks of Physics are: %.2f\n",(float)mean_marks_phy/(float)count);
    printf("The average marks of Chemistry are: %.2f\n",(float)mean_marks_chem/(float)count);
    printf("The average marks of Maths are: %.2f\n",(float)mean_marks_math/(float)count);
    printf("The average marks of Computer Science are: %.2f\n",(float)mean_marks_cs/(float)count);
    fclose(fptr);}

void generate_rp(){
    info temp;
    FILE *fptr;
    int rollno,found=0;
    printf("Enter the Roll No. whose report card you want to generate:");
    scanf("%d",&rollno);
    char line[512];
    fptr=fopen(FILENAME,"r");
    if(!fptr){
        printf("Error opening the file\n");
        return;}
    while(fgets(line,sizeof(line),fptr)){
        if (parse_line(line, &temp) != 11) continue;

        if(rollno==temp.roll_no){
            found=1;
            break;}}
    if(found==0){
        printf("No such record found");
        fclose(fptr);
        return;}

    int total = temp.marks[0] + temp.marks[1] + temp.marks[2] + temp.marks[3] + temp.marks[4];
    
    char *subjects[5] = {"English", "Physics", "Chemistry", "Maths", "Computer Science"};
    
    char grade;
    if (temp.percentage >= 90) grade = 'A';
    else if (temp.percentage >= 80) grade = 'B';
    else if (temp.percentage >= 70) grade = 'C';
    else if (temp.percentage >= 60) grade = 'D';
    else grade = 'E';

    printf("\n====================================================\n");
    printf("                 REPORT CARD                        \n");
    printf("====================================================\n");
    printf("Name      : %s\n", temp.name);
    printf("Roll No   : %d\n", temp.roll_no);
    printf("Class     : %s\n", temp.class);
    printf("Phone No. : %s\n", temp.phone_no);
    printf("E-Mail    : %s\n", temp.email);
    printf("----------------------------------------------------\n");
    printf(" Subject              Marks (out of 100)\n");
    printf("----------------------------------------------------\n");
    printf(" %-20s %3d\n", subjects[0], temp.marks[0]);
    printf(" %-20s %3d\n", subjects[1], temp.marks[1]);
    printf(" %-20s %3d\n", subjects[2], temp.marks[2]);
    printf(" %-20s %3d\n", subjects[3], temp.marks[3]);
    printf(" %-20s %3d\n", subjects[4], temp.marks[4]);
    printf("----------------------------------------------------\n");
    printf(" Total Marks : %d / 500\n", total);
    printf(" Percentage  : %.2f %%\n", temp.percentage);
    printf(" Grade       : %c\n", grade);
    printf("====================================================\n\n"); 
    fclose(fptr);
};

int main(){
    // write_headers();
    info students[MAX_STUDENTS];
    int student_count=0;
    printf("===================================================================================================================================\n");
    printf("                                                    STUDENT RECORD MANAGEMENT SYSTEM                                                     \n");
    printf("===================================================================================================================================\n");
    printf("\n\n");
    if (!login()) {
        system("pause");
        return 0;}
    while(1){
        int b;
        printf("\n\n");
        printf("[1] Add new student record\n");
        printf("[2] Display all records\n");
        printf("[3] Search student by roll number\n");
        printf("[4] Search student by name\n");
        printf("[5] Percentage of a particular roll no.\n");
        printf("[6] Overall Class Topper\n");
        printf("[7] Topper of a particular subject\n");
        printf("[8] Students who need guidance (%%<50)\n");
        printf("[9] Update student's record\n");
        printf("[10] Delete a record.\n");
        printf("[11] Display mean marks scored by students in each subject\n");
        printf("[12] Generate report card of a particular roll no.\n");
        printf("[13] Exit\n");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%d",&b);
        printf("\n");
        switch(b){
            case 1:
                new_entry(students,&student_count);
                break;
            case 2:
                display_record();
                break;
            case 3:
                stu_by_roll();
                break;
            case 4:
                stu_by_name();
                break;
            case 5:
                parti_per();
                break;
            case 6:
                class_topper();
                break;
            case 7:
                subject_topper();
                break;
            case 8:
                needy();
                break;
            case 9:
                update();
                break;
            case 10:
                delete_record();
                break;
            case 11:
                mean_marks();
                break;
            case 12:
                generate_rp();
                break;
            case 13:
                save_exit();
                break;
            default:
                printf("Invalid input");

        }
    }
}

