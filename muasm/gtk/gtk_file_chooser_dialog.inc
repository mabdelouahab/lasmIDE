    GTK_FILE_CHOOSER_ACTION_OPEN = 0
    GTK_FILE_CHOOSER_ACTION_SAVE = 1
    GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER = 2
    GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER = 3
    
    GTK_RESPONSE_NONE = -1
    GTK_RESPONSE_REJECT = -2
    GTK_RESPONSE_ACCEPT = -3
    GTK_RESPONSE_DELETE_EVENT = -4
    GTK_RESPONSE_OK = -5
    GTK_RESPONSE_CANCEL = -6
    GTK_RESPONSE_CLOSE = -7
    GTK_RESPONSE_YES = -8
    GTK_RESPONSE_NO = -9
    GTK_RESPONSE_APPLY = -10
    GTK_RESPONSE_HELP = -11
    
    gtk_file_chooser_dialog_new  PROTO 	__title		:gpointer,\
    					__parent	:gpointer,\
    					__action 	:dword,\
    					button_id	:VARARG 
                             
