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

//window
GtkWidget  *window;

//containers
GtkWidget  *main_frame;
GtkWidget  *first_btns;
GtkWidget  *sec_btns;
GtkWidget  *dc_win;
GtkWidget  *dc_viewp;
GtkWidget  *dc_grid;


//buttons
GtkWidget  *m_decks;
GtkWidget  *m_cards;
GtkWidget  *add_btn;
GtkWidget  *rem_btn;
GtkWidget  *exit_btn;


//rows of cards and decks
GtkWidget *label[1000];
GtkWidget *button[1000];


//builder
GtkBuilder *builder;


char tmp[1024];
int row;

void on_m_decks_clicked(GtkButton *b)
{
	printf("m_decks\n");
}

void on_m_cards_clicked(GtkButton *b)
{
	printf("m_cards\n");
}
void on_add_btn_clicked(GtkButton *b)
{
	printf("add_btn\n");
}
void on_rem_btn_clicked(GtkButton *b)
{
	printf("rem_btn\n");
}
void on_exit_btn_clicked (GtkButton *b)
{
	printf("exit_btn\n");
}

void on_row(GtkButton *b)
{
	printf("%s\n",gtk_button_get_label(b));
}



int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	
	
	builder = gtk_builder_new_from_file("Ui_teste.glade");
	
	window = GTK_WIDGET(gtk_builder_get_object(builder,"gtk_window"));
	g_signal_connect(window,"destroy", G_CALLBACK(gtk_main_quit),NULL);
	
	gtk_builder_connect_signals(builder,NULL);
	
	//load buttons
	m_decks = GTK_WIDGET(gtk_builder_get_object(builder,"m_decks"));
	m_cards = GTK_WIDGET(gtk_builder_get_object(builder,"m_cards"));
	add_btn = GTK_WIDGET(gtk_builder_get_object(builder,"add_btn"));
	rem_btn = GTK_WIDGET(gtk_builder_get_object(builder,"rem_btn"));
	exit_btn = GTK_WIDGET(gtk_builder_get_object(builder,"exit_btn"));
	
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
	
	//load deck file
	FILE *f1 = fopen("Decks.txt", "r");
	if(f1==NULL)
	{
		printf("File error!\n");
		return 1;
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
		
		//label[row] = gtk_label_new (tmp);
		//gtk_label_set_justify (GTK_LABEL(label[row]), GTK_JUSTIFY_LEFT);
		//gtk_label_set_xalign (GTK_LABEL(label[row]), 0.0);
		//gtk_grid_attach (GTK_GRID(dc_grid), label[row], 1, row, 1, 1);
		//gtk_widget_show(label[row]);
		//printf("%s\n",tmp);
		button[row] = gtk_button_new_with_label(tmp);
		gtk_button_set_alignment(GTK_BUTTON(button[row]),0.0,0.5);
		gtk_grid_attach(GTK_GRID(dc_grid), button[row], 1, row, 1, 1);
		g_signal_connect(button[row], "clicked", G_CALLBACK(on_row),NULL);
		gtk_widget_show(button[row]);
		row++;
		
		
	}
	
	
	gtk_widget_show(window);
	
	gtk_main();
	
	
	return 0;
}



