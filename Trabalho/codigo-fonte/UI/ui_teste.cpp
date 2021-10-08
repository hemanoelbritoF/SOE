#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <sys/mman.h>
#include <dirent.h> 
#include <stdio.h> 


//window
GtkWidget  *window;

//containers
GtkWidget  *main_frame;
GtkWidget  *first_btns;
GtkWidget  *sec_btns;
GtkWidget  *dc_win;
GtkWidget  *dc_viewp;
GtkWidget  *dc_grid;
GtkWidget  *text_entry;
GtkWidget  *method_selector;



//buttons
GtkWidget  *m_decks;
GtkWidget  *m_cards;
GtkWidget  *add_btn;
GtkWidget  *rem_btn;
GtkWidget  *exit_btn;
GtkWidget  *back_btn;
GtkWidget  *enter_btn;
GtkWidget  *camera_btn;
GtkWidget  *manual_btn;
GtkWidget  *back_btn2;

//text entry
GtkWidget  *get_usr_entry;

//rows of cards and decks
GtkWidget *label[1000];
GtkWidget *button[1000];
char actual_deck[1024];


//builder
GtkBuilder *builder;

//aux
char tmp[1024];
char tmp2[1024];
int row = 0;
int cd_flag = 0;
int rem_flag = 0;

void on_m_decks_clicked(GtkButton *);
void on_m_cards_clicked(GtkButton *);
void on_add_btn_clicked(GtkButton *);
void on_rem_btn_clicked(GtkButton *);
void on_exit_btn_clicked (GtkButton *);
void on_back_btn_clicked (GtkButton *);
void on_enter_btn_clicked (GtkButton *);
void on_camera_btn_clicked (GtkButton *);
void on_manual_btn_clicked (GtkButton *);
void on_back_btn2_clicked (GtkButton *);
void on_row(GtkButton *);
void on_row2(GtkButton *);
void delete_rows();
void update_list();




int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	
	
	builder = gtk_builder_new_from_file("Ui_teste.glade");
	//load windows
	window = GTK_WIDGET(gtk_builder_get_object(builder,"gtk_window"));
	text_entry = GTK_WIDGET(gtk_builder_get_object(builder,"text_entry"));
	method_selector = GTK_WIDGET(gtk_builder_get_object(builder,"method_selector"));
	
	g_signal_connect(window,"destroy", G_CALLBACK(gtk_main_quit),NULL);
	
	
	gtk_builder_connect_signals(builder,NULL);
	
	//load buttons
	m_decks = GTK_WIDGET(gtk_builder_get_object(builder,"m_decks"));
	m_cards = GTK_WIDGET(gtk_builder_get_object(builder,"m_cards"));
	add_btn = GTK_WIDGET(gtk_builder_get_object(builder,"add_btn"));
	rem_btn = GTK_WIDGET(gtk_builder_get_object(builder,"rem_btn"));
	back_btn = GTK_WIDGET(gtk_builder_get_object(builder,"back_btn"));
	enter_btn = GTK_WIDGET(gtk_builder_get_object(builder,"enter_btn"));
	camera_btn = GTK_WIDGET(gtk_builder_get_object(builder,"camera_btn"));
	manual_btn = GTK_WIDGET(gtk_builder_get_object(builder,"manual_btn"));
	back_btn2 = GTK_WIDGET(gtk_builder_get_object(builder,"back_btn2"));
	
	//usr entry
	get_usr_entry = GTK_WIDGET(gtk_builder_get_object(builder,"get_usr_entry"));
	
	//load list
	dc_win = GTK_WIDGET(gtk_builder_get_object(builder,"dc_win"));
	dc_viewp = GTK_WIDGET(gtk_builder_get_object(builder,"dc_viewp"));
	dc_grid = GTK_WIDGET(gtk_builder_get_object(builder,"dc_grid"));
	
	
	//connect signals
	g_signal_connect(m_decks,"clicked",G_CALLBACK(on_m_decks_clicked),NULL);
	g_signal_connect(m_cards,"clicked",G_CALLBACK(on_m_cards_clicked),NULL);
	g_signal_connect(add_btn,"clicked",G_CALLBACK(on_add_btn_clicked),NULL);
	g_signal_connect(rem_btn,"clicked",G_CALLBACK(on_rem_btn_clicked),NULL);
	g_signal_connect(exit_btn,"clicked",G_CALLBACK(on_exit_btn_clicked),NULL);
	g_signal_connect(back_btn,"clicked",G_CALLBACK(on_back_btn_clicked),NULL);
	g_signal_connect(enter_btn,"clicked",G_CALLBACK(on_enter_btn_clicked),NULL);
	g_signal_connect(back_btn2,"clicked",G_CALLBACK(on_back_btn2_clicked),NULL);
	g_signal_connect(manual_btn,"clicked",G_CALLBACK(on_manual_btn_clicked),NULL);
	
	//start window
	
	
	
	gtk_widget_show(window);
	gtk_widget_hide(text_entry);
	gtk_widget_hide(method_selector);
	
	gtk_main();
	
	
	return 0;
}

void on_m_decks_clicked(GtkButton *b)
{
	cd_flag = 1;
	
	update_list();
	
}

void on_m_cards_clicked(GtkButton *b)
{
	cd_flag = 2;
	sprintf(actual_deck, "%s", "AllCards"); 
	update_list();
	
}
void on_add_btn_clicked(GtkButton *b)
{
	if(cd_flag == 1)
	{
		gtk_widget_show_all(text_entry);
	}
	if(cd_flag == 2)
	{
		gtk_widget_show_all(method_selector);
	}
	
}
void on_rem_btn_clicked(GtkButton *b)
{
	if(rem_flag == 1)
	{
		GdkColor color;

		gdk_color_parse ("blue", &color);

		gtk_widget_modify_bg ( GTK_WIDGET(b), GTK_STATE_NORMAL, &color);
		rem_flag=0;
	}
	else if(rem_flag == 0)
	{
		GdkColor color;

		gdk_color_parse ("red", &color);

		gtk_widget_modify_bg ( GTK_WIDGET(b), GTK_STATE_NORMAL, &color);
		rem_flag=1;
	}
	printf("%d\n",rem_flag);
}
void on_exit_btn_clicked (GtkButton *b)
{
	exit(0);
}

void on_row(GtkButton *b)
{
	//make file string
	char txt[] = ".txt";
	char file_name[1024];
	sprintf(file_name, "%s", gtk_button_get_label(b));  
	strcat(file_name,txt);
	
	if(rem_flag==1)
	{
		if(cd_flag == 1)
		{
			int n = 0;
			while(1)
			{
				GtkWidget* temp = gtk_grid_get_child_at(GTK_GRID(dc_grid),1, n);
				if(GTK_BUTTON(temp) == b)
					break;
				n++;
				
			}
			
			
			system("cp Decks.txt aux.txt");
			
			FILE *f1 = fopen("aux.txt", "r");
			if(f1==NULL)
			{
				printf("File error!\n");
				return;
			}
			
			system("rm Decks.txt");
			system("touch Decks.txt");
			row=0;
			while(1)
			{
				if(fgets(tmp,1024,f1)==NULL)
				{
					fclose(f1);
					break;
				}
				printf("ndos0-------=%d\n",n);
				if(!row == n)
				{
					
					tmp[strlen(tmp)-1] = 0;
					char cmd_append[2048] = "echo ";
					strcat(cmd_append,tmp);
					printf("%s\n",cmd_append);
					
					system(cmd_append);
					strcat(cmd_append,">>Decks.txt");
					printf("%s\n",cmd_append);
					system(cmd_append);
				}
				row++;
			}
			
			
			char remove_file[1024] = "rm ";
			strcat(remove_file,file_name);
			system(remove_file);
			
			update_list();
			return;
		}
	}
	else
	{
		
		sprintf(actual_deck, "%s", gtk_button_get_label(b)); 
		printf("%s\n",actual_deck);
		//reset grid
		
		
		update_list();
		cd_flag = 2; 
	}
}

void on_back_btn_clicked (GtkButton *b)
{
	gtk_editable_delete_text(GTK_EDITABLE(get_usr_entry),0,-1);
	gtk_widget_hide(text_entry);
}

void on_enter_btn_clicked (GtkButton *b)
{
	if(cd_flag == 1)
	{
		
		printf("%s\n",gtk_entry_get_text(GTK_ENTRY(get_usr_entry)));
		char txt[] = ".txt";
		char file_name[1024], file_namecp[1024];
		
		sprintf(file_name, "%s", gtk_entry_get_text(GTK_ENTRY(get_usr_entry)));  
		strcpy(file_namecp,file_name);
		strcat(file_name,txt);
		
		FILE *f1 = fopen(file_name, "r");
		if(f1==NULL)
		{
				
			char start_cmd[2048] = "echo ";
			char start_cmd2[2048] = "echo ";
			char end_cmd[] = " >> Decks.txt";
			char end_cmd2[] = "touch ";
			char end_cmd3[] = "touch ";
			
			//adiciona o deck a colecao
			strcat(start_cmd,file_namecp);
			strcat(start_cmd,end_cmd);
			system(start_cmd);
			
			//cria o arquivo do deck
			//strcat(start_cmd2,end_cmd2);
			strcat(end_cmd2,file_name);
			system(end_cmd2);
			
			//cria o arquivo de n de cartas
			strcat(end_cmd3,"q");
			strcat(end_cmd3,file_name);
			system(end_cmd3);
			
			printf("%s\n",end_cmd3);
			update_list();
			
			gtk_editable_delete_text(GTK_EDITABLE(get_usr_entry),0,-1);
			gtk_widget_hide(text_entry);
			return;
		}
		
		
		update_list();
		
		gtk_editable_delete_text(GTK_EDITABLE(get_usr_entry),0,-1);
		gtk_widget_hide(text_entry);
	}
	
	if(cd_flag == 2)
	{
			char txt[] = ".txt";
			char card_name[1024];
			
			char file_name[1024], file_namecp[1024];
			char append_cmd[1024] = "echo ";
			char append_cmd2[1024] = "echo ";
			char actual_deck_q[1024] = "q";
			char actual_deck_aux[1024] = "q";
			char actual_deck_aux2[1024] = "q";
			
			strcpy(actual_deck_aux,actual_deck);
			strcpy(actual_deck_aux2,actual_deck);
			
			
			strcat(actual_deck_aux, txt);
			
			sprintf(card_name, "%s",  gtk_entry_get_text(GTK_ENTRY(get_usr_entry)));  
			
			//add card to deck
			strcat(append_cmd, card_name);
			strcat(append_cmd, ">>");
			strcat(append_cmd, actual_deck_aux);
			system(append_cmd);
			
			strcat(append_cmd2, "1");
			strcat(append_cmd2, " >> ");
			strcat(actual_deck_q,actual_deck_aux2);
			strcat(actual_deck_q,txt);
			
			strcat(append_cmd2, actual_deck_q);
			printf("%s\n",append_cmd2);
			system(append_cmd2);
			
			//make buttons and append to grid
			gtk_editable_delete_text(GTK_EDITABLE(get_usr_entry),0,-1);
			gtk_widget_hide(text_entry);
			update_list();
			
	}
	
	
}

void delete_rows()
{
	GList *children, *iter;
	children = gtk_container_get_children(GTK_CONTAINER(dc_grid));
	for (iter = children; iter!=NULL; iter = g_list_next(iter))
	{
		gtk_widget_destroy(GTK_WIDGET(iter->data));

	}
	g_list_free(children);
}

void update_list()
{
	delete_rows();
	if(cd_flag == 1)
	{
		
		
		delete_rows();
		FILE *f1 = fopen("Decks.txt", "r");
		if(f1==NULL)
		{
			printf("File error!\n");
			exit(1);
		}
		
		//make buttons and append to grid
		row=0;
		while(1)
		{
			if(fgets(tmp,1024,f1)==NULL)
			{
				fclose(f1);
				break;
			}
			tmp[strlen(tmp)-1] = 0;
			
			gtk_grid_insert_row(GTK_GRID(dc_grid), row);

			//add buttons
			button[row] = gtk_button_new_with_label(tmp);
			gtk_button_set_alignment(GTK_BUTTON(button[row]),0.0,0.5);
			gtk_grid_attach(GTK_GRID(dc_grid), button[row], 1, row, 1, 1);
			g_signal_connect(button[row], "clicked", G_CALLBACK(on_row),NULL);
			gtk_widget_show(button[row]);
			row++;
			
			
		}
	}
	
	if(cd_flag == 2)
	{
		char txt[] = ".txt";
		char actual_deck_aux[1024] = "q";
		char actual_deck_aux2[1024] = "q";
		strcpy(actual_deck_aux,actual_deck);
		strcat(actual_deck_aux,txt);
		
		delete_rows();
		printf("%s\n",actual_deck_aux);
		FILE *f1 = fopen(actual_deck_aux, "r");
		strcat(actual_deck_aux2,actual_deck_aux);
		FILE *f2 = fopen(actual_deck_aux2, "r");
		if(f1==NULL||f2==NULL)
		{
			printf("File error!\n");
			exit(1);
		}
		
		//make buttons and append to grid
		row=0;
		while(1)
		{
			if(fgets(tmp,1024,f1)==NULL||fgets(tmp2,1024,f2)==NULL)
			{
				fclose(f1);
				fclose(f2);
				break;
			}
			tmp[strlen(tmp)-1] = 0;
			tmp2[strlen(tmp2)-1] = 0;
			
			gtk_grid_insert_row(GTK_GRID(dc_grid), row);
			strcat(tmp2,"x");
			strcat(tmp2,tmp);
			printf("%s\n",tmp2);
			button[row] = gtk_button_new_with_label(tmp2);
			gtk_button_set_alignment(GTK_BUTTON(button[row]),0.0,0.5);
			gtk_grid_attach(GTK_GRID(dc_grid), button[row], 1, row, 1, 1);
			g_signal_connect(button[row], "clicked", G_CALLBACK(on_row2),NULL);
			gtk_widget_show(button[row]);
			row++;
			
			
		}
	}
	
}

void on_row2(GtkButton *b)
{
	if(rem_flag==1)
	{
		char buff[100];
			int val_n = 0;
			while(1)
			{
				
				GtkWidget* temp = gtk_grid_get_child_at(GTK_GRID(dc_grid),1,val_n);
				if(GTK_BUTTON(temp) == b)
					break;
				
				val_n++;
				
				
			}
			sprintf(buff,"%d",val_n);
			printf("%d\n",atoi(buff));
			
			
			
			char cmd_append[] = "cp ";
			strcat(cmd_append,"q");
			strcat(cmd_append,actual_deck);
			strcat(cmd_append,".txt ");
			strcat(cmd_append,"aux.txt");
			system(cmd_append);
			
			FILE *f1 = fopen("aux.txt", "r");
			if(f1==NULL)
			{
				printf("File error!\n");
				return;
			}
			
			
			char cmd_append2[] = "rm ";
			strcat(cmd_append2,"q");
			strcat(cmd_append2,actual_deck);
			strcat(cmd_append2,".txt");
			system(cmd_append2);
			
			char cmd_append3[] = "touch ";
			strcat(cmd_append3,"q");
			strcat(cmd_append3,actual_deck);
			strcat(cmd_append3,".txt");
			system(cmd_append3);
			
			row=0;
			while(1)
			{
				
				if(fgets(tmp,1024,f1)==NULL)
				{
					fclose(f1);
					break;
				}
				tmp[strlen(tmp)-1] = 0;
				char cmd_append4[2048] = "echo ";
				
				if(row == atoi(buff))
				{
					printf("-----------chegou aqui0\n");
					
					
					int val = atoi(tmp);
					val--;
					if(val!=0)
					{
					
					
					sprintf(tmp,"%d",val);
					strcat(cmd_append4,tmp);
					printf("cmd4%s\n",cmd_append4);
					
					strcat(cmd_append4," >> ");
					strcat(cmd_append4,"q");
					strcat(cmd_append4,actual_deck);
					strcat(cmd_append4,".txt");
					printf("%s\n",cmd_append4);
					
					system(cmd_append4);
					}
					
					
				}
				else
				{
				
					
					strcat(cmd_append4,tmp);
					printf("%s\n",cmd_append4);
					
					system(cmd_append4);
					strcat(cmd_append4," >> ");
					strcat(cmd_append4,"q");
					strcat(cmd_append4,actual_deck);
					strcat(cmd_append4,".txt");
					printf("cmd4:%s\n",cmd_append4);
					system(cmd_append4);
				}
				row++;
			}
			update_list();
	
	}
	else
	{
			char buff[100];
			int val_n = 0;
			while(1)
			{
				
				GtkWidget* temp = gtk_grid_get_child_at(GTK_GRID(dc_grid),1,val_n);
				if(GTK_BUTTON(temp) == b)
					break;
				
				val_n++;
				
				
				
			}
			sprintf(buff,"%d",val_n);
			printf("%d\n",atoi(buff));
			
			
			
			char cmd_append[] = "cp ";
			strcat(cmd_append,"q");
			strcat(cmd_append,actual_deck);
			strcat(cmd_append,".txt ");
			strcat(cmd_append,"aux.txt");
			system(cmd_append);
			
			FILE *f1 = fopen("aux.txt", "r");
			if(f1==NULL)
			{
				printf("File error!\n");
				return;
			}
			
			
			char cmd_append2[] = "rm ";
			strcat(cmd_append2,"q");
			strcat(cmd_append2,actual_deck);
			strcat(cmd_append2,".txt");
			system(cmd_append2);
			
			char cmd_append3[] = "touch ";
			strcat(cmd_append3,"q");
			strcat(cmd_append3,actual_deck);
			strcat(cmd_append3,".txt");
			system(cmd_append3);
			
			row=0;
			while(1)
			{
				
				if(fgets(tmp,1024,f1)==NULL)
				{
					fclose(f1);
					break;
				}
				tmp[strlen(tmp)-1] = 0;
				char cmd_append4[2048] = "echo ";
				
				if(row == atoi(buff))
				{
					printf("-----------chegou aqui0\n");
					
					
					int val = atoi(tmp);
					val++;
					
					sprintf(tmp,"%d",val);
					strcat(cmd_append4,tmp);
					printf("cmd4%s\n",cmd_append4);
					
					strcat(cmd_append4," >> ");
					strcat(cmd_append4,"q");
					strcat(cmd_append4,actual_deck);
					strcat(cmd_append4,".txt");
					printf("%s\n",cmd_append4);
					
					system(cmd_append4);
					
					
					
				}
				else
				{
				
					
					strcat(cmd_append4,tmp);
					printf("%s\n",cmd_append4);
					
					system(cmd_append4);
					strcat(cmd_append4," >> ");
					strcat(cmd_append4,"q");
					strcat(cmd_append4,actual_deck);
					strcat(cmd_append4,".txt");
					printf("cmd4:%s\n",cmd_append4);
					system(cmd_append4);
				}
				row++;
			}
			update_list();
	}
	
}

void on_camera_btn_clicked (GtkButton *b)
{
	
}
void on_manual_btn_clicked (GtkButton *b)
{
	gtk_widget_show(text_entry);
	
}
void on_back_btn2_clicked (GtkButton *b)
{
	gtk_widget_hide(method_selector);
}

