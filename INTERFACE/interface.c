#include "interface.h"

// Make them global

GtkWidget	*window;
GtkWidget	*fixed1;
GtkWidget	*button1;
GtkWidget	*button2;
GtkWidget	*button3;
GtkWidget       *button4;
GtkWidget       *button5;
GtkWidget       *button6;
GtkWidget       *button7;
GtkWidget       *button8;
GtkWidget       *button9;
GtkWidget       *button10;
GtkWidget       *button11;
GtkWidget       *button12;
GtkWidget       *button13;
GtkWidget	*button14;

GtkWidget	*label1;
GtkWidget	*label2;
GtkWidget       *label3;

GtkWidget	*spin1;
GtkWidget	*file1;
GtkWidget	*image1;
GtkWidget	*image2;

GtkBuilder	*builder; 

GtkListStore	*liststore1;
GtkAdjustment	*adjustment2;

gchar 		*path;

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); // init Gtk

//---------------------------------------------------------------------
// establish contact with xml code used to adjust widget settings
//---------------------------------------------------------------------
 
	builder = gtk_builder_new_from_file ("interface.glade");
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        gtk_builder_connect_signals(builder, NULL);

	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
	button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
	button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
	button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
        button5 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
        button6 = GTK_WIDGET(gtk_builder_get_object(builder, "button6"));
	button7 = GTK_WIDGET(gtk_builder_get_object(builder, "button7"));
	button8 = GTK_WIDGET(gtk_builder_get_object(builder, "button8"));
	button9 = GTK_WIDGET(gtk_builder_get_object(builder, "button9"));
	button10 = GTK_WIDGET(gtk_builder_get_object(builder, "button10"));
	button11 = GTK_WIDGET(gtk_builder_get_object(builder, "button11"));
	button12 = GTK_WIDGET(gtk_builder_get_object(builder, "button12"));
	button13 = GTK_WIDGET(gtk_builder_get_object(builder, "button13"));
	button14 = GTK_WIDGET(gtk_builder_get_object(builder, "button14"));

	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
	label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
        label3 = GTK_WIDGET(gtk_builder_get_object(builder, "label3"));

	spin1 = GTK_WIDGET(gtk_builder_get_object(builder, "spin1"));
	file1 = GTK_WIDGET(gtk_builder_get_object(builder, "file1"));
	image2 = GTK_WIDGET(gtk_builder_get_object(builder, "image2"));

	liststore1 = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));
	adjustment2 = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment2"));

	gtk_widget_show(window);

	image1 = NULL; 

	//rotation
	gtk_widget_set_sensitive(button1, FALSE);
	//display
	gtk_widget_set_sensitive(button2, TRUE);
	//grayscale
	gtk_widget_set_sensitive(button3, FALSE);
	//display rotation
	gtk_widget_set_sensitive(button4, FALSE);
	//black and white
	gtk_widget_set_sensitive(button5, FALSE);
	//grid only
	gtk_widget_set_sensitive(button6, FALSE);
	//SU DO KU
	gtk_widget_set_sensitive(button7, TRUE);
        //auto rotation
	gtk_widget_set_sensitive(button8, FALSE);
	//Pre traitment
	gtk_widget_set_sensitive(button9, FALSE);
	//Train
	gtk_widget_set_sensitive(button10, TRUE);
	//solve grid
	gtk_widget_set_sensitive(button11, FALSE);
        //color grid
	gtk_widget_set_sensitive(button12, FALSE);
        //display resolved sudoku
	gtk_widget_set_sensitive(button13, FALSE);
	//Identification
	gtk_widget_set_sensitive(button14, FALSE);

	gtk_main();

	return EXIT_SUCCESS;
}


//MANUAL ROTATE BUTTON
void	on_button1_clicked() //(GtkButton *b) 
{
	char tmp[128];
	gdouble val = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spin1));
	sprintf(tmp, "spin=%d", (int) val);
	gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) tmp);

	SaveRotation(path, (int)val);
	ResizeRotation();

	char filename[] = "../Black_and_white/Images/Rotation_resized.bmp";

        int hor = 150, ver = 1;
        if (image1)
                gtk_container_remove (GTK_CONTAINER (fixed1), image1); // remove old slide
        gtk_widget_hide(image2);
        image1 = gtk_image_new_from_file (filename);
        gtk_container_add (GTK_CONTAINER (fixed1), image1);
        gtk_widget_show(image1);
        gtk_fixed_move (GTK_FIXED(fixed1), image1, hor, ver);


	gtk_label_set_text (GTK_LABEL(label3), "If you want to rotate this image again you can find it at\n Black_and_white/Images/Rotate.bmp and display it.\nIf it is not perfect you can let me do it for you with auto rotation !\nOtherwise you can lend it to me, I will do the pre-traitment!");
	gtk_label_set_text (GTK_LABEL(label2), "To display the original interface with the logo, please press the button on the top left.");


	gtk_widget_set_sensitive(button4, TRUE);

}


//FILE CHOOSER
void	on_file1_file_set(GtkFileChooserButton *f) 
{
	printf("file name = %s\n", gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(f)) );
	printf("folder name = %s\n", gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER(f)) );
	
	path = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(f));
	gtk_label_set_text (GTK_LABEL(label1), path);
}



//DISPLAY BUTTON
void	on_button2_clicked() //(GtkButton *b) 
{
  	int hor = 150, ver = 1;
        if (image1)
                gtk_container_remove (GTK_CONTAINER (fixed1), image1); // remove old slide
        gtk_widget_hide(image2);
        image1 = gtk_image_new_from_file (path);
        gtk_container_add (GTK_CONTAINER (fixed1), image1);
        gtk_widget_show(image1);
        gtk_fixed_move (GTK_FIXED(fixed1), image1, hor, ver);


	gtk_label_set_text(GTK_LABEL(label3),"Keep in mind that the image you have displayed will be the one I will process,\nyou can always change it at any time! If your image is not straight you can turn it\nyourself by choosing an angle and pressing the rotate button or ask me to do it\nfor you with Auto rotate! If all is good you can let me do the pre-treatment!");
	gtk_label_set_text (GTK_LABEL(label2), "To display the original interface with the logo, please press the button on the top left.");


	//manual rotate
	gtk_widget_set_sensitive(button1, TRUE);
	//auto rotate
	gtk_widget_set_sensitive(button8, TRUE);
        //work work work
	gtk_widget_set_sensitive(button9, TRUE);

	//grayscale	
	gtk_widget_set_sensitive(button3, FALSE);
	//rotate
	gtk_widget_set_sensitive(button4, FALSE);
	//black and white
	gtk_widget_set_sensitive(button5, FALSE);
	//grid detected
	gtk_widget_set_sensitive(button6, FALSE);
	//solve
	gtk_widget_set_sensitive(button11, FALSE);

}


//GRAYSCALE BUTTON
void	on_button3_clicked() //(GtkButton *b) 
{
	char filename[] = "../Black_and_white/Images/Grayscale_resized.bmp";
	int hor = 150, ver = 1;
	if (image1) 
		gtk_container_remove (GTK_CONTAINER (fixed1), image1); // remove old slide
	gtk_widget_hide(image2);
        image1 = gtk_image_new_from_file (filename);
        gtk_container_add (GTK_CONTAINER (fixed1), image1);
        gtk_widget_show(image1);
        gtk_fixed_move (GTK_FIXED(fixed1), image1, hor, ver);
}


//ROTATED BUTTON
void    on_button4_clicked()//(GtkButton *b) 
{
        char filename[] = "../Black_and_white/Images/Rotation_resized.bmp";
        int hor = 150, ver = 1;
        if (image1)
                gtk_container_remove (GTK_CONTAINER (fixed1), image1); // remove old slide
        gtk_widget_hide(image2);
        image1 = gtk_image_new_from_file (filename);
        gtk_container_add (GTK_CONTAINER (fixed1), image1);
        gtk_widget_show(image1);
        gtk_fixed_move (GTK_FIXED(fixed1), image1, hor, ver);

}



//BLACK AND WHITE BUTTON
void    on_button5_clicked()//(GtkButton *b)
{
        char filename[] = "../Black_and_white/Images/BlackandWhite_resized.bmp";
        int hor = 150, ver = 1;
        if (image1)
                gtk_container_remove (GTK_CONTAINER (fixed1), image1); // remove old slide
        gtk_widget_hide(image2);
        image1 = gtk_image_new_from_file (filename);
        gtk_container_add (GTK_CONTAINER (fixed1), image1);
        gtk_widget_show(image1);
        gtk_fixed_move (GTK_FIXED(fixed1), image1, hor, ver);
}


//GRID BUTTON
void    on_button6_clicked()//(GtkButton *b)
{
        char filename[] = "../EXTRACT_TILES/TreatedImages/image_grid_only_resized.bmp";
        int hor = 150, ver = 1;
        if (image1)
                gtk_container_remove (GTK_CONTAINER (fixed1), image1); // remove old slide
        gtk_widget_hide(image2);
        image1 = gtk_image_new_from_file (filename);
        gtk_container_add (GTK_CONTAINER (fixed1), image1);
        gtk_widget_show(image1);
        gtk_fixed_move (GTK_FIXED(fixed1), image1, hor, ver);

	gtk_label_set_text (GTK_LABEL(label3), "Now if you want to solve the sudoku, you have to start the identification\nof the numbers already present in the grid with the button on the right.");
}


//DISPLAY LOGO BUTTON
void    on_button7_clicked()
{
        char filename[] = "sudoku.png";
        int hor = 150, ver = 1;
        if (image1)
                gtk_container_remove (GTK_CONTAINER (fixed1), image1); // remove old slide
        gtk_widget_hide(image2);
        image1 = gtk_image_new_from_file (filename);
        gtk_container_add (GTK_CONTAINER (fixed1), image1);
        gtk_widget_show(image1);
        gtk_fixed_move (GTK_FIXED(fixed1), image1, hor, ver);
}

//AUTO ROTATION BUTTON
void    on_button8_clicked()//(GtkButton *b)
{

	traitment(path);

	ExtractGrid("../Black_and_white/Images/BlackandWhite_dilatation.bmp");

	int alpha = angle_from_path("../EXTRACT_TILES/TreatedImages/image_grid_only.bmp");


	gchar str[32] = "";
	(void)g_snprintf(str, 32, "Angle calculated : %d", alpha);
	gtk_label_set_text (GTK_LABEL(label1), str);

	SaveRotation(path, alpha);
	ResizeRotation();

        char filename[] = "../Black_and_white/Images/Rotation_resized.bmp";
        int hor = 150, ver = 1;
        if (image1)
                gtk_container_remove (GTK_CONTAINER (fixed1), image1); // remove old slide
        gtk_widget_hide(image2);
        image1 = gtk_image_new_from_file (filename);
        gtk_container_add (GTK_CONTAINER (fixed1), image1);
        gtk_widget_show(image1);
        gtk_fixed_move (GTK_FIXED(fixed1), image1, hor, ver);


        gtk_label_set_text (GTK_LABEL(label2), 	"If your sudoku is upside down, you can select it again with the file chooser\nand rotate it by 90 or 180 degrees with the manual rotation.");

	gtk_widget_set_sensitive(button4, TRUE);
}


//TRAITEMENT IMAGE BUTTON
void    on_button9_clicked()//(GtkButton *b)
{
	//manual rotate
	gtk_widget_set_sensitive(button1, FALSE);
	//display
	//gtk_widget_set_sensitive(button2, FALSE);
	//auto rotation
	gtk_widget_set_sensitive(button8, FALSE);
	//work work work
	gtk_widget_set_sensitive(button9, FALSE);
	
	
	//grayscale
        gtk_widget_set_sensitive(button3, TRUE);
        //black and white
        gtk_widget_set_sensitive(button5, TRUE);
        //grid detected
        gtk_widget_set_sensitive(button6, TRUE);
	//solve
	gtk_widget_set_sensitive(button11, TRUE);
        //grid colored
        gtk_widget_set_sensitive(button12, TRUE);
	//identification
	gtk_widget_set_sensitive(button14, TRUE);

	traitment(path);

	ExtractGrid("../Black_and_white/Images/BlackandWhite.bmp");
	ExtractTile("../Black_and_white/Images/BlackandWhite.bmp");
	GetResizedImages();

	gtk_label_set_text (GTK_LABEL(label3), "Wow! That was a lot of work, now you can see all the results with\nthe buttons that I have unlocked for you on the right.");
        gtk_label_set_text (GTK_LABEL(label2), "To display the original interface with the logo, please press the button on the top left.");

}



//TRAIN BUTTON
void    on_button10_clicked()//(GtkButton *b)
{
	Neural_Network nn;
	Images_Set set;
	Fill_Set(&set);
	NetworkInit(&nn);
    NN_Train(&nn, &set);
	//NN_Test(&nn, &set);

}

//SOLVE BUTTON
void    on_button11_clicked()//(GtkButton *b)
{

	Solve_Sudoku("grid_01.txt");
	PrintResult("grid_01.txt", "grid_01.result.txt");
	gtk_widget_set_sensitive(button13, TRUE);
}


//COLORIZED GRID BUTTON
void    on_button12_clicked()//(GtkButton *b)
{

	char filename[] = "../EXTRACT_TILES/TreatedImages/image_colorized_resized.bmp";
        int hor = 150, ver = 1;
        if (image1)
                gtk_container_remove (GTK_CONTAINER (fixed1), image1); // remove old slide
        gtk_widget_hide(image2);
        image1 = gtk_image_new_from_file (filename);
        gtk_container_add (GTK_CONTAINER (fixed1), image1);
        gtk_widget_show(image1);
        gtk_fixed_move (GTK_FIXED(fixed1), image1, hor, ver);

        gtk_label_set_text (GTK_LABEL(label2), "Pretty right ?");


}

//RESOLVED SUDOKU BUTTON
void    on_button13_clicked()//(GtkButton *b)
{

	char filename[] = "../EXTRACT_TILES/TreatedImages/image_solved.bmp";
        int hor = 150, ver = 1;
        if (image1)
                gtk_container_remove (GTK_CONTAINER (fixed1), image1); // remove old slide
        gtk_widget_hide(image2);
        image1 = gtk_image_new_from_file (filename);
        gtk_container_add (GTK_CONTAINER (fixed1), image1);
        gtk_widget_show(image1);
        gtk_fixed_move (GTK_FIXED(fixed1), image1, hor, ver);

	gtk_label_set_text (GTK_LABEL(label3),"");
	gtk_label_set_text (GTK_LABEL(label2), "Wow we made it! After all this way together, it was a great adventure.\nIf you want to start over you can choose a new image with the file chooser.");
}

//IDENTIFICATION BUTTON
void on_button14_clicked()
{
    Neural_Network nn;
    if(access( ".save_nn", F_OK) == 0)
    {
        NN_Load(&nn, ".save_nn");
        images2txt(&nn);

	gtk_label_set_text (GTK_LABEL(label2), "I read and convert your Sudoku into text, now you can ask me to resolve it for you !");
        gtk_label_set_text(GTK_LABEL(label3), "");
    }
    else
    {
	gtk_label_set_text (GTK_LABEL(label2), "Oh! It seems that you don't have some trained neural network yet. I can try one for you if you clicked on train.");
	gtk_label_set_text(GTK_LABEL(label3), "");
    }
}
