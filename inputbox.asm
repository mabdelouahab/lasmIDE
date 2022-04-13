IFNDEF WedgInputBox_user_value
.DATA
    WedgInputBox_user_value              gpointer    0
    WedgInputBox_WInputBox               gpointer    0
    WedgInputBox_WBtnOk                  gpointer    0
    WedgInputBox_WBtnCance               gpointer    0
    WedgInputBox_WValue                  gpointer    0
    

.CODE
    user_input_box proc WedgInputBox_arg_text:gpointer,WedgInputBox_arg_titl:gpointer
        local lbuilder  :gpointer
        local lWedgInputBox_arg_titl  :gpointer
        local lWedgInputBox_arg_text  :gpointer
        mov lWedgInputBox_arg_titl,WedgInputBox_arg_titl
        mov lWedgInputBox_arg_text,WedgInputBox_arg_text
        mov lbuilder,rv(gtk_builder_new)
        invoke gtk_builder_add_from_string, lbuilder,addr InputBoxInterface ,-1,0
        .if rax
            mov WedgInputBox_WInputBox       ,rv(gtk_builder_get_object, lbuilder,str$("WInputBox"))
            .if lWedgInputBox_arg_titl
                invoke gtk_window_set_title,WedgInputBox_WInputBox,lWedgInputBox_arg_titl
            .endif
                
            mov WedgInputBox_WBtnOk          ,rv(gtk_builder_get_object, lbuilder,str$("WBtnOk"))
            mov WedgInputBox_WBtnCance       ,rv(gtk_builder_get_object, lbuilder,str$("WBtnCance"))
            mov WedgInputBox_WValue          ,rv(gtk_builder_get_object, lbuilder,str$("WValue"))
            .if lWedgInputBox_arg_text
                invoke gtk_label_set_text,rv(gtk_builder_get_object, lbuilder,str$("WIBCaption")),lWedgInputBox_arg_text                
            .endif
            
            invoke gtk_widget_set_sensitive,WedgInputBox_WBtnOk, 0   

        ;    invoke g_signal_connect_data,WedgInputBox_WInputBox    ,str$("destroy")    ,addr gtk_main_quit       ,0,0,0     

            invoke g_signal_connect_data,WedgInputBox_WValue       ,str$("changed")    ,addr On_WedgInputBox_WValue_changed    ,0,0,0     
            invoke g_signal_connect_data,WedgInputBox_WBtnOk       ,str$("clicked")    ,addr On_WedgInputBox_WBtnOk_clicked    ,0,0,0     
            invoke g_signal_connect_data,WedgInputBox_WBtnCance    ,str$("clicked")    ,addr On_WedgInputBox_WBtnCance_clicked    ,0,0,0     
            
            invoke gtk_window_set_modal,WedgInputBox_WInputBox,GTK_DIALOG_MODAL
            ;invoke gtk_widget_show_all ,WedgInputBox_WInputBox
            invoke g_object_unref,lbuilder
            invoke gtk_dialog_run,WedgInputBox_WInputBox
            invoke gtk_widget_destroy,WedgInputBox_WInputBox  
            .if WedgInputBox_user_value
                mov rax,WedgInputBox_user_value
            .else
                xor rax,rax
            .endif
        .else
        invoke printf,str$(<13,10,"ELSE  ">)
            xor rax,rax
        .endif
        RET
    user_input_box endp
    
    On_WedgInputBox_WBtnOk_clicked PROC
        invoke gtk_entry_get_text,WedgInputBox_WValue
        invoke g_strdup,rax
        mov WedgInputBox_user_value,rax
        invoke printf,str$(<13,10,"WedgInputBox_user_value OKbutton=%s ">),WedgInputBox_user_value
        invoke gtk_dialog_response,WedgInputBox_WInputBox,-5
        RET
    On_WedgInputBox_WBtnOk_clicked ENDP
    On_WedgInputBox_WBtnCance_clicked PROC
        invoke printf,str$(<13,10,"On_WedgInputBox_WBtnCance_clicked ">)
        mov WedgInputBox_user_value,0 
        invoke gtk_dialog_response,WedgInputBox_WInputBox,-5
        RET
    On_WedgInputBox_WBtnCance_clicked ENDP
    On_WedgInputBox_WValue_changed PROC
        .if rv( gtk_entry_get_text_length,WedgInputBox_WValue) == 0
            invoke gtk_widget_set_sensitive,WedgInputBox_WBtnOk, 0          
        .else
            invoke gtk_widget_set_sensitive,WedgInputBox_WBtnOk, -1          
        .endif        
        RET
    On_WedgInputBox_WValue_changed ENDP
    
    
    
.DATA
    InputBoxInterface	DB	'<?xml version="1.0" encoding="UTF-8"?>'
            		DB	'<interface>'
            		DB	'  <object class="GtkDialog" id="WInputBox">'
            		DB	'    <property name="visible">True</property>'
            		DB	'    <property name="can_focus">False</property>'
            		DB	'    <property name="type_hint">dialog</property>'
            		DB	'    <child>'
            		DB	'      <placeholder/>'
            		DB	'    </child>'
            		DB	'    <child internal-child="vbox">'
            		DB	'      <object class="GtkBox">'
            		DB	'        <property name="can_focus">False</property>'
            		DB	'        <property name="orientation">vertical</property>'
            		DB	'        <property name="spacing">2</property>'
            		DB	'        <child internal-child="action_area">'
            		DB	'          <object class="GtkButtonBox">'
            		DB	'            <property name="can_focus">False</property>'
            		DB	'            <property name="layout_style">end</property>'
            		DB	'            <child>'
            		DB	'              <object class="GtkButton" id="WBtnOk">'
            		DB	'                <property name="label" translatable="yes">Ok</property>'
            		DB	'                <property name="visible">True</property>'
            		DB	'                <property name="can_focus">True</property>'
            		DB	'                <property name="receives_default">True</property>'
            		DB	'              </object>'
            		DB	'              <packing>'
            		DB	'                <property name="expand">True</property>'
            		DB	'                <property name="fill">True</property>'
            		DB	'                <property name="position">0</property>'
            		DB	'              </packing>'
            		DB	'            </child>'
            		DB	'            <child>'
            		DB	'              <object class="GtkButton" id="WBtnCance">'
            		DB	'                <property name="label" translatable="yes">Cancel</property>'
            		DB	'                <property name="visible">True</property>'
            		DB	'                <property name="can_focus">True</property>'
            		DB	'                <property name="receives_default">True</property>'
            		DB	'              </object>'
            		DB	'              <packing>'
            		DB	'                <property name="expand">True</property>'
            		DB	'                <property name="fill">True</property>'
            		DB	'                <property name="position">1</property>'
            		DB	'              </packing>'
            		DB	'            </child>'
            		DB	'          </object>'
            		DB	'          <packing>'
            		DB	'            <property name="expand">False</property>'
            		DB	'            <property name="fill">False</property>'
            		DB	'            <property name="position">0</property>'
            		DB	'          </packing>'
            		DB	'        </child>'
            		DB	'        <child>'
            		DB	'          <object class="GtkBox">'
            		DB	'            <property name="visible">True</property>'
            		DB	'            <property name="can_focus">False</property>'
            		DB	'            <child>'
            		DB	'              <object class="GtkEntry" id="WValue">'
            		DB	'                <property name="visible">True</property>'
            		DB	'                <property name="can_focus">True</property>'
            		DB	'              </object>'
            		DB	'              <packing>'
            		DB	'                <property name="expand">False</property>'
            		DB	'                <property name="fill">True</property>'
            		DB	'                <property name="pack_type">end</property>'
            		DB	'                <property name="position">0</property>'
            		DB	'              </packing>'
            		DB	'            </child>'
            		DB	'            <child>'
            		DB	'              <object class="GtkLabel" id="WIBCaption">'
            		DB	'                <property name="height_request">27</property>'
            		DB	'                <property name="visible">True</property>'
            		DB	'                <property name="can_focus">False</property>'
            		DB	'                <property name="label" translatable="yes">Value:  </property>'
            		DB	'                <property name="justify">center</property>'
            		DB	'              </object>'
            		DB	'              <packing>'
            		DB	'                <property name="expand">False</property>'
            		DB	'                <property name="fill">True</property>'
            		DB	'                <property name="pack_type">end</property>'
            		DB	'                <property name="position">1</property>'
            		DB	'              </packing>'
            		DB	'            </child>'
            		DB	'          </object>'
            		DB	'          <packing>'
            		DB	'            <property name="expand">False</property>'
            		DB	'            <property name="fill">True</property>'
            		DB	'            <property name="position">1</property>'
            		DB	'          </packing>'
            		DB	'        </child>'
            		DB	'      </object>'
            		DB	'    </child>'
            		DB	'  </object>'
            		DB	'</interface>',0
            
ENDIF