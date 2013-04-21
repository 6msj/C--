/* simulator - Dev-CPP 5 version

   virtual machine simulator that executes intermediate language so as to
   be the last module of PL/H interpreter.  simulator is initialized from
   codefile and datafile, which are created either through text editing or
   running parser.
   */

/* include files */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

/* define array size constants */
#define  CODE_SIZE  1000
#define  DATA_SIZE  1000
#define  STACK_SIZE  100

/* define miscellaneous constants */
#define  STR_SIZE  80
/* size of our standard string type 'str' */
const char strfield[]="%s";  /* for input into variables of type str */
//const int true=1;  //uncomment with a C compiler
//const int false=0;
const char fwd[]="%5d";
const char fws[]="%5s";

/* define types */
typedef char str[STR_SIZE+1];
/* our standard string type.  allocates storage */
typedef char strparam[];
/*  type for formal parameter strings.  doesn't allocate storage */
//typedef int bool;  //uncomment with a C compiler

/* define variables */
str code[CODE_SIZE];  /* code memory */
int pc;
/* program counter.  during execution phase, points to instruction */
/* being executed */
int data[DATA_SIZE];  /* data memory */
int stack[STACK_SIZE];  /* stack register */
int top;
/* always indexes top of stack.  top=0 indicates stack is empty */
bool running;
bool sim_trace=true;
/* determines whether a simulator trace will be produced */
bool SendOutputToFile=false;
/*when true, standard output is redirected to a text file */
FILE *outfilep;  /* file pointer for redirected output */

/* function prototypes */
void cycle(void);
void push(int);
int immed_op(void);
int pop(void);
void push(int j);
void simpic(void);
void initialize(void);
void read_files(void);
bool eqstr(strparam s, strparam t);

/*
Note:
i=atoi("-123"); leaves -123 in int variable i.
sprintf(s, "%d", -123); leaves "-123" in string variable s.
atoi is in stdlib.h, and sprintf is in stdio.h.
*/

/********************************************************************/
int main(void)
{
    sim_trace=true;
    SendOutputToFile=true;
    initialize();
    cycle();
end: puts("simulator done");
     if (!SendOutputToFile)
     {
         puts("push Enter to leave User Window");  /* for Turbo C++ */
         getchar();
     }
     exit(0);
} /* end main */
/*********************************************************************/
void cycle(void)
    /* main cycle of simulator */
{
    str opcode;
    int top_op, under_op;

    if (sim_trace)
        puts("starting simulator execution");
    running=true;
    while (running)
    {
        /* increment pc and fetch next instruction */

        ++pc;

        strcpy(opcode,code[pc]);
        if (sim_trace) simpic();

        /* do case on opcode */
        if (eqstr(opcode,"quit"))
        {
            puts("********** simulator quit instruction executed");
            puts("");
            running=false;
        }

        // Homework  || and, or, not, inc, dec ||
        
       else if (eqstr(opcode,"and")) {
           push(pop() && pop());
       } else if(eqstr(opcode,"or")) {
           push(pop() || pop());
       } else if(eqstr(opcode,"not")) {
           push(!pop());
       } else if(eqstr(opcode,"inc")) {
           top_op = immed_op();
           push(pop() + top_op);
       } else if(eqstr(opcode,"dec")) {
           top_op = immed_op();
           push(pop() - top_op);
       }

        /**/
        /*  load/store instructions */
        else if (eqstr(opcode,"load"))
            push(data[immed_op()]);
        else if (eqstr(opcode,"store"))
            data[immed_op()]=pop();
        else if (eqstr(opcode,"lit"))
            push(immed_op());
        else if (eqstr(opcode,"ldi"))
            push(data[pop()]);
        else if (eqstr(opcode,"sti"))
        {
            top_op=pop();
            data[pop()]=top_op;
        }
        /**/
        /* arithmetic instructions */
        else if (eqstr(opcode,"add"))
            push(pop()+pop());
        else if (eqstr(opcode,"sub"))
        {
            top_op=pop();
            push(pop()-top_op);
        }
        else if (eqstr(opcode,"mult"))
            push(pop()*pop());
        else if (eqstr(opcode,"div"))
        {
            top_op=pop();
            if(top_op==0)
            {
                puts("********** VM attempted a divide by 0");
                puts(" ");
                running=false;
            }
            else
                push(pop()/top_op);
        }
        else if (eqstr(opcode,"neg"))
            push(-pop());
        /**/
        /* relational instructions */
        else if (eqstr(opcode,"eq"))
        {
            top_op=pop(); under_op=pop();
            push(under_op==top_op ?  1 : 0);
        }
        else if (eqstr(opcode,"lt"))
        {
            top_op=pop(); under_op=pop();
            push(under_op<top_op ?  1 : 0);
        }
        else if (eqstr(opcode,"gt"))
        {
            top_op=pop(); under_op=pop();
            push(under_op>top_op ?  1 : 0);
        }
        else if (eqstr(opcode,"ne"))
        {
            top_op=pop(); under_op=pop();
            push(under_op!=top_op ?  1 : 0);
        }
        else if (eqstr(opcode,"le"))
        {
            top_op=pop(); under_op=pop();
            push(under_op<=top_op ?  1 : 0);
        }
        else if (eqstr(opcode,"ge"))
        {
            top_op=pop(); under_op=pop();
            push(under_op>=top_op ?  1 : 0);
        }
        /**/
        /* branch instructions */
        else if (eqstr(opcode,"br"))
            pc=pop()-1;
        else if (eqstr(opcode,"brl"))
            pc=immed_op()-1;
        else if (eqstr(opcode,"brf"))
        {
            top_op=pop(); under_op=pop();
            if(under_op==0)
                pc=top_op-1;
        }
        /**/
        /* input/output instructions */
        else if (eqstr(opcode,"out"))
            printf("********** simulator output=%d\n",pop());
        else if (eqstr(opcode,"in"))
        {
            scanf("%d",&top_op);
            if(SendOutputToFile)
                printf("input from keyboard=%d\n", top_op);
            push(top_op);
        }
        else
            printf("invalid opcode=%s\n",opcode);
    }
}  /* end cycle */
/************************************************************************/
int immed_op(void)
    /* increment pc and return code[pc] as an integer rather than as a string */
{
    ++pc;
    return(atoi(code[pc]));
}  /* end immed_op */
/***********************************************************************/
void simpic(void)
    /* produce a 3 line picture of the state of the simulator */
{
    int j;
    str opcode;

    /* separate picture from previous with blank line */
    puts("");

    /* show stack */
    printf("stack ");
    for (j=top; j>=1; --j)
        printf(fwd,stack[j]);
    printf("\n");

    /* show initial part of data memory */
    printf("data ");
    for (j=1; j<=5; ++j)
        printf(fwd,data[j]);
    printf("\n");

    /* show instruction about to be executed */
    strcpy(opcode, code[pc]);
    printf("%s",opcode);
    if (eqstr(opcode,"load") ||
            eqstr(opcode,"store") ||
            eqstr(opcode,"lit"))
        /* then */
        printf(" %s",code[pc+1]);
    printf("   at %d\n",pc);

    /* prompt user to continue */
    if (SendOutputToFile)
        return;  /* no need for any prompts */
    puts("push Enter to continue");
    getchar();
}  /* end simpic */
/**********************************************************************/
void initialize(void)
    /* initialize simulator */
{
    read_files();
    pc=0;  /* causes execution to begin with code[1] */
    top=0;  /* initializes stack empty */

    /* from now on, send output to a text file rather than screen,
       if flag set */
    if(SendOutputToFile)
    {
        outfilep=freopen("simulout.txt", "wt", stdout);
        if(outfilep==NULL)
            printf("error in redirecting stdout to file simulout.txt");
    }
}  /* end initialize */
/**********************************************************************/
void read_files(void)
    /* read into code and data arrays from text files codefile and datafile */
{
    FILE *codefilep, *datafilep;
    /* file pointers for text files from which code and data arrays are */
    /* initialized.  each line of these files initializes one array */
    /* element. */
    int j;

    /* read codefile */
    codefilep=fopen("codefile","r");
    if (codefilep==NULL)
    {
        puts("error in trying to open codefile");
        puts("push Enter to leave User Window");
        getchar();
        exit(1);
    }

    j=0;  /* will start initializing with code[1] */
    while (!feof(codefilep))
    {
        ++j;
        fscanf(codefilep, strfield, code[j]);
    }
    fclose(codefilep);

    /* read datafile */
    datafilep=fopen("datafile","r");
    if (datafilep==NULL)
    {
        puts("error in trying to open datafile");
        puts("push Enter to leave User Window");
        getchar();
        exit(1);
    }

    j=0;  /* will start initializing with data[1] */
    while (!feof(datafilep))
    {
        ++j;
        fscanf(datafilep, "%d", &data[j]);
    }
    fclose(datafilep);
}  /* end read_files */
/*************************************************************************/
int pop(void)
    /* pop simulator stack and return value popped */
{
    --top;
    return(stack[top+1]);
}  /* end pop */
/************************************************************************/
void push(int j)
    /* push j onto simulator stack */
{
    ++top;
    stack[top]=j;
}  /* end push */
/************************************************************************/
bool eqstr(strparam s, strparam t)
    /* eqstr <- true iff s=t */
{
    return(!strcmp(s,t));
}  /* end eqstr */
/************************************************************************/

