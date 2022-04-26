
_GdkEventKey    struct 8
    type_   QWORD    ?               ;8
    window  QWORD   ?                          ;8
    send_event      DWORD   ?       ;4
    time    DWORD ?              ;4
    state   DWORD   ?              ;4
    keyval  DWORD   ?              ;4           ;until here is right, bellow can be wrong size
    length_ DWORD    ?              ;4
    string  QWORD   ?              ;8
    hardware_keycode        DWORD ?      ;
    group_  DWORD  ?              ;
    GdkEventKey_R0 DWORD ?
_GdkEventKey    ends

GdkModifierType typedef qWORD
GDK_SHIFT_MASK = 1  shl  0
GDK_LOCK_MASK = 1  shl  1
GDK_CONTROL_MASK = 1  shl  2
GDK_MOD1_MASK = 1  shl  3
GDK_MOD2_MASK = 1  shl  4
GDK_MOD3_MASK = 1  shl  5
GDK_MOD4_MASK = 1  shl  6
GDK_MOD5_MASK = 1  shl  7
GDK_BUTTON1_MASK = 1  shl  8
GDK_BUTTON2_MASK = 1  shl  9
GDK_BUTTON3_MASK = 1  shl  10
GDK_BUTTON4_MASK = 1  shl  11
GDK_BUTTON5_MASK = 1  shl  12
GDK_SUPER_MASK = 1  shl  26
GDK_HYPER_MASK = 1  shl  27
GDK_META_MASK = 1  shl  28
GDK_RELEASE_MASK = 1  shl  30
GDK_MODIFIER_MASK = 5c001fffh


_GdkRectangle   struct
x       dword    ?
y       dword   ?
width_  dword   ?
height  dword   ?
_GdkRectangle   ends

gtk_font_chooser_get_font  proto :vararg
gtk_font_chooser_dialog_new proto :vararg
gtk_font_selection_dialog_new proto :vararg
gtk_font_selection_dialog_get_font_name  proto :vararg
pango_font_description_from_string  proto :vararg
gtk_color_selection_dialog_new proto :vararg
gtk_color_chooser_dialog_new proto :vararg
gtk_color_chooser_get_rgba proto :vararg
gdk_color_to_string proto :vararg
g_strsplit proto :vararg
gtk_expander_new proto :vararg
gtk_expander_set_expanded proto :vararg

gdk_rgba_to_string proto :vararg
gdk_rgba_parse proto :vararg
gtk_source_completion_words_new proto :vararg
gtk_source_completion_words_register proto :vararg
gtk_source_completion_add_provider proto :vararg
gtk_check_menu_item_toggled proto :vararg
gtk_check_menu_item_get_active proto :vararg

TRUE EQU 1
NULL EQU 0
FALSE EQU 0
GTK_TEXT_WINDOW_WIDGET EQU 1
GTK_WINDOW_POPUP EQU 1
GTK_WRAP_NONE EQU 0
GTK_WRAP_WORD_CHAR EQU 3
GTK_STYLE_PROVIDER_PRIORITY_USER EQU 800
G_FILE_TEST_EXISTS = 1  shl  4

_GtkTextIter    struct
    dummy1  gpointer        ?
    dummy2  gpointer        ?
    dummy3  gint    ?
    dummy4  gint    ?
    dummy5  gint    ?
    dummy6  gint    ?
    dummy7  gint    ?
    dummy8  gint    ?
    dummy9  gpointer        ?
    dummy10 gpointer        ?
    dummy11 gint    ?
    dummy12 gint    ?
    dummy13 gint    ?
    dummy14 gpointer        ?
_GtkTextIter    ends

GError typedef ptr _GError
GQuark typedef guint32

GError typedef ptr _GError
_GError struct 8
domain GQuark ?
code   gint ?
message gpointer ?  ;gchar       *
_GError ends


