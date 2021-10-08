#include <gtk/gtk.h>
#include <fstream>

int main(int argc, char *argv[]) {

  GtkWidget *window;
  GtkWidget *vbox;// caixa de decks (*decks)
  GtkWidget *vbox2;//segunda caixa de botoes (add/rem/sair)
  GtkWidget *vbox3;//primeira caixa de botoes (Decks/cards)

  
  GtkWidget *add;//adicionar
  GtkWidget *rem;//remover
  GtkWidget *exit;//sair
  GtkWidget *m_decks;//meus decks
  GtkWidget *m_cards;//minhas cartas
  
  GtkWidget *debts;
  GtkWidget *settings;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  
  gtk_window_set_default_size(GTK_WINDOW(window), 230, 250);
  gtk_window_set_title(GTK_WINDOW(window), "TCG ID");
  gtk_container_set_border_width(GTK_CONTAINER(window), 5);
  
  //list
  //GtkListStore *ls = gtk_list_store_new(100, G_TYPE_STRING);//list
  //GdkPixbuf *icon = gtk_icon_theme_load_icon(gtk_icon_theme_get_default(), "dialog-ok-apply", 32, GTK_ICON_LOOKUP_USE_BUILTIN, NULL);//icones
  int pos = 0;
  
  //subsections
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
  vbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
  vbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

  
  
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_container_add(GTK_CONTAINER(vbox), vbox3);
  gtk_container_add(GTK_CONTAINER(vbox), vbox2);
  
 

  
  add = gtk_button_new_with_label("Add");
  rem = gtk_button_new_with_label("Rem");
  exit = gtk_button_new_with_label("Sair");
  debts = gtk_button_new_with_label("Debts");
  settings = gtk_button_new_with_label("Settings");
  m_decks = gtk_button_new_with_label("Decks");
  m_cards = gtk_button_new_with_label("Cards");

  //buttons1
  gtk_box_pack_start(GTK_BOX(vbox3), m_decks, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox3), m_cards, TRUE, TRUE, 0);
  
  //buttons2
  gtk_box_pack_start(GTK_BOX(vbox2), add, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(vbox2), rem, TRUE, TRUE, 2);
  gtk_box_pack_start(GTK_BOX(vbox2), exit, TRUE, TRUE, 0);
  
  //deck list

  std::ifstream file("Decks.txt");//abre o arquivo com os nomes de decks
  if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) //itera pelas linhas
		{
			//gtk_list_store_insert_with_values(ls, NULL, pos++, 0, line.c_str(), 1);//adiciona a lista cada carta
			pos++;
			printf("%s\n", line.c_str());
		}
		file.close();
  }else
  {
	printf("11");  
  }
  printf("2"); 

  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  gtk_widget_show_all(window);

  gtk_main();
  
  return 0;
}
