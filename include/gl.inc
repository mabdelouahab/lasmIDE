IFNDEF	__gl_INCh
		__gl_INC	EQU	1h
		

	GLenum                  typedef dword
	GLboolean               typedef byte
	GLbitfield              typedef dword
	GLbyte                  typedef sbyte
	GLshort                 typedef sword
	GLint                   typedef sdword
	GLsizei                 typedef sdword
	GLubyte                 typedef byte
	GLushort                typedef word
	GLuint                  typedef dword
	GLfloat                 typedef real4
	GLclampf                typedef real4
	GLdouble                typedef real8
	GLclampd                typedef real8
	GLvoid                  equ <>



	GL_VERSION_1_1          equ 1
	GL_ACCUM                EQU 00100h
	GL_LOAD                 EQU 00101h
	GL_RETURN               EQU 00102h
	GL_MULT                 EQU 00103h
	GL_ADD                  EQU 00104h
	GL_NEVER                EQU 00200h
	GL_LESS                 EQU 00201h
	GL_EQUAL                EQU 00202h
	GL_LEQUAL               EQU 00203h
	GL_GREATER              EQU 00204h
	GL_NOTEQUAL             EQU 00205h
	GL_GEQUAL               EQU 00206h
	GL_ALWAYS               EQU 00207h
	GL_CURRENT_BIT          EQU 000000001h
	GL_POINT_BIT            EQU 000000002h
	GL_LINE_BIT             EQU 000000004h
	GL_POLYGON_BIT          EQU 000000008h
	GL_POLYGON_STIPPLE_BIT  EQU 000000010h
	GL_PIXEL_MODE_BIT       EQU 000000020h
	GL_LIGHTING_BIT         EQU 000000040h
	GL_FOG_BIT              EQU 000000080h
	GL_DEPTH_BUFFER_BIT     EQU 000000100h
	GL_ACCUM_BUFFER_BIT     EQU 000000200h
	GL_STENCIL_BUFFER_BIT   EQU 000000400h
	GL_VIEWPORT_BIT         EQU 000000800h
	GL_TRANSFORM_BIT        EQU 000001000h
	GL_ENABLE_BIT           EQU 000002000h
	GL_COLOR_BUFFER_BIT     EQU 000004000h
	GL_HINT_BIT             EQU 000008000h
	GL_EVAL_BIT             EQU 000010000h
	GL_LIST_BIT             EQU 000020000h
	GL_TEXTURE_BIT          EQU 000040000h
	GL_SCISSOR_BIT          EQU 000080000h
	GL_ALL_ATTRIB_BITS      EQU 0000fffffh
	GL_POINTS               EQU 00000h
	GL_LINES                EQU 00001h
	GL_LINE_LOOP            EQU 00002h
	GL_LINE_STRIP           EQU 00003h
	GL_TRIANGLES            EQU 00004h
	GL_TRIANGLE_STRIP       EQU 00005h
	GL_TRIANGLE_FAN         EQU 00006h
	GL_QUADS                EQU 00007h
	GL_QUAD_STRIP           EQU 00008h
	GL_POLYGON              EQU 00009h
	GL_ZERO                 equ 0
	GL_ONE                  equ 1
	GL_SRC_COLOR            EQU 00300h
	GL_ONE_MINUS_SRC_COLOR  EQU 00301h
	GL_SRC_ALPHA            EQU 00302h
	GL_ONE_MINUS_SRC_ALPHA  EQU 00303h
	GL_DST_ALPHA            EQU 00304h
	GL_ONE_MINUS_DST_ALPHA  EQU 00305h
	GL_DST_COLOR            EQU 00306h
	GL_ONE_MINUS_DST_COLOR  EQU 00307h
	GL_SRC_ALPHA_SATURATE   EQU 00308h
	GL_TRUE                 equ 1
	GL_FALSE                equ 0
	GL_CLIP_PLANE0          EQU 03000h
	GL_CLIP_PLANE1          EQU 03001h
	GL_CLIP_PLANE2          EQU 03002h
	GL_CLIP_PLANE3          EQU 03003h
	GL_CLIP_PLANE4          EQU 03004h
	GL_CLIP_PLANE5          EQU 03005h
	GL_BYTE                 EQU 01400h
	GL_UNSIGNED_BYTE        EQU 01401h
	GL_SHORT                EQU 01402h
	GL_UNSIGNED_SHORT       EQU 01403h
	GL_INT                  EQU 01404h
	GL_UNSIGNED_INT         EQU 01405h
	GL_FLOAT                EQU 01406h
	GL_2_BYTES              EQU 01407h
	GL_3_BYTES              EQU 01408h
	GL_4_BYTES              EQU 01409h
	GL_DOUBLE               EQU 0140Ah
	GL_NONE                 equ 0
	GL_FRONT_LEFT           EQU 00400h
	GL_FRONT_RIGHT          EQU 00401h
	GL_BACK_LEFT            EQU 00402h
	GL_BACK_RIGHT           EQU 00403h
	GL_FRONT                EQU 00404h
	GL_BACK                 EQU 00405h
	GL_LEFT                 EQU 00406h
	GL_RIGHT                EQU 00407h
	GL_FRONT_AND_BACK       EQU 00408h
	GL_AUX0                 EQU 00409h
	GL_AUX1                 EQU 0040Ah
	GL_AUX2                 EQU 0040Bh
	GL_AUX3                 EQU 0040Ch
	GL_NO_ERROR             equ 0
	GL_INVALID_ENUM         EQU 00500h
	GL_INVALID_VALUE        EQU 00501h
	GL_INVALID_OPERATION    EQU 00502h
	GL_STACK_OVERFLOW       EQU 00503h
	GL_STACK_UNDERFLOW      EQU 00504h
	GL_OUT_OF_MEMORY        EQU 00505h
	GL_2D                   EQU 00600h
	GL_3D                   EQU 00601h
	GL_3D_COLOR             EQU 00602h
	GL_3D_COLOR_TEXTURE     EQU 00603h
	GL_4D_COLOR_TEXTURE     EQU 00604h
	GL_PASS_THROUGH_TOKEN   EQU 00700h
	GL_POINT_TOKEN          EQU 00701h
	GL_LINE_TOKEN           EQU 00702h
	GL_POLYGON_TOKEN        EQU 00703h
	GL_BITMAP_TOKEN         EQU 00704h
	GL_DRAW_PIXEL_TOKEN     EQU 00705h
	GL_COPY_PIXEL_TOKEN     EQU 00706h
	GL_LINE_RESET_TOKEN     EQU 00707h
	GL_EXP                  EQU 00800h
	GL_EXP2                 EQU 00801h
	GL_CW                   EQU 00900h
	GL_CCW                  EQU 00901h
	GL_COEFF                EQU 00A00h
	GL_ORDER                EQU 00A01h
	GL_DOMAIN               EQU 00A02h
	GL_CURRENT_COLOR        EQU 00B00h
	GL_CURRENT_INDEX        EQU 00B01h
	GL_CURRENT_NORMAL       EQU 00B02h
	GL_CURRENT_TEXTURE_COORDS EQU 00B03h
	GL_CURRENT_RASTER_COLOR EQU 00B04h
	GL_CURRENT_RASTER_INDEX EQU 00B05h
	GL_CURRENT_RASTER_TEXTURE_COORDS EQU 00B06h
	GL_CURRENT_RASTER_POSITION EQU 00B07h
	GL_CURRENT_RASTER_POSITION_VALID EQU 00B08h
	GL_CURRENT_RASTER_DISTANCE EQU 00B09h
	GL_POINT_SMOOTH         EQU 00B10h
	GL_POINT_SIZE           EQU 00B11h
	GL_POINT_SIZE_RANGE     EQU 00B12h
	GL_POINT_SIZE_GRANULARITY EQU 00B13h
	GL_LINE_SMOOTH          EQU 00B20h
	GL_LINE_WIDTH           EQU 00B21h
	GL_LINE_WIDTH_RANGE     EQU 00B22h
	GL_LINE_WIDTH_GRANULARITY EQU 00B23h
	GL_LINE_STIPPLE         EQU 00B24h
	GL_LINE_STIPPLE_PATTERN EQU 00B25h
	GL_LINE_STIPPLE_REPEAT  EQU 00B26h
	GL_LIST_MODE            EQU 00B30h
	GL_MAX_LIST_NESTING     EQU 00B31h
	GL_LIST_BASE            EQU 00B32h
	GL_LIST_INDEX           EQU 00B33h
	GL_POLYGON_MODE         EQU 00B40h
	GL_POLYGON_SMOOTH       EQU 00B41h
	GL_POLYGON_STIPPLE      EQU 00B42h
	GL_EDGE_FLAG            EQU 00B43h
	GL_CULL_FACE            EQU 00B44h
	GL_CULL_FACE_MODE       EQU 00B45h
	GL_FRONT_FACE           EQU 00B46h
	GL_LIGHTING             EQU 00B50h
	GL_LIGHT_MODEL_LOCAL_VIEWER EQU 00B51h
	GL_LIGHT_MODEL_TWO_SIDE EQU 00B52h
	GL_LIGHT_MODEL_AMBIENT  EQU 00B53h
	GL_SHADE_MODEL          EQU 00B54h
	GL_COLOR_MATERIAL_FACE  EQU 00B55h
	GL_COLOR_MATERIAL_PARAMETER EQU 00B56h
	GL_COLOR_MATERIAL       EQU 00B57h
	GL_FOG                  EQU 00B60h
	GL_FOG_INDEX            EQU 00B61h
	GL_FOG_DENSITY          EQU 00B62h
	GL_FOG_START            EQU 00B63h
	GL_FOG_END              EQU 00B64h
	GL_FOG_MODE             EQU 00B65h
	GL_FOG_COLOR            EQU 00B66h
	GL_DEPTH_RANGE          EQU 00B70h
	GL_DEPTH_TEST           EQU 00B71h
	GL_DEPTH_WRITEMASK      EQU 00B72h
	GL_DEPTH_CLEAR_VALUE    EQU 00B73h
	GL_DEPTH_FUNC           EQU 00B74h
	GL_ACCUM_CLEAR_VALUE    EQU 00B80h
	GL_STENCIL_TEST         EQU 00B90h
	GL_STENCIL_CLEAR_VALUE  EQU 00B91h
	GL_STENCIL_FUNC         EQU 00B92h
	GL_STENCIL_VALUE_MASK   EQU 00B93h
	GL_STENCIL_FAIL         EQU 00B94h
	GL_STENCIL_PASS_DEPTH_FAIL EQU 00B95h
	GL_STENCIL_PASS_DEPTH_PASS EQU 00B96h
	GL_STENCIL_REF          EQU 00B97h
	GL_STENCIL_WRITEMASK    EQU 00B98h
	GL_MATRIX_MODE          EQU 00BA0h
	GL_NORMALIZE            EQU 00BA1h
	GL_VIEWPORT             EQU 00BA2h
	GL_MODELVIEW_STACK_DEPTH EQU 00BA3h
	GL_PROJECTION_STACK_DEPTH EQU 00BA4h
	GL_TEXTURE_STACK_DEPTH  EQU 00BA5h
	GL_MODELVIEW_MATRIX     EQU 00BA6h
	GL_PROJECTION_MATRIX    EQU 00BA7h
	GL_TEXTURE_MATRIX       EQU 00BA8h
	GL_ATTRIB_STACK_DEPTH   EQU 00BB0h
	GL_CLIENT_ATTRIB_STACK_DEPTH EQU 00BB1h
	GL_ALPHA_TEST           EQU 00BC0h
	GL_ALPHA_TEST_FUNC      EQU 00BC1h
	GL_ALPHA_TEST_REF       EQU 00BC2h
	GL_DITHER               EQU 00BD0h
	GL_BLEND_DST            EQU 00BE0h
	GL_BLEND_SRC            EQU 00BE1h
	GL_BLEND                EQU 00BE2h
	GL_LOGIC_OP_MODE        EQU 00BF0h
	GL_INDEX_LOGIC_OP       EQU 00BF1h
	GL_COLOR_LOGIC_OP       EQU 00BF2h
	GL_AUX_BUFFERS          EQU 00C00h
	GL_DRAW_BUFFER          EQU 00C01h
	GL_READ_BUFFER          EQU 00C02h
	GL_SCISSOR_BOX          EQU 00C10h
	GL_SCISSOR_TEST         EQU 00C11h
	GL_INDEX_CLEAR_VALUE    EQU 00C20h
	GL_INDEX_WRITEMASK      EQU 00C21h
	GL_COLOR_CLEAR_VALUE    EQU 00C22h
	GL_COLOR_WRITEMASK      EQU 00C23h
	GL_INDEX_MODE           EQU 00C30h
	GL_RGBA_MODE            EQU 00C31h
	GL_DOUBLEBUFFER         EQU 00C32h
	GL_STEREO               EQU 00C33h
	GL_RENDER_MODE          EQU 00C40h
	GL_PERSPECTIVE_CORRECTION_HINT EQU 00C50h
	GL_POINT_SMOOTH_HINT    EQU 00C51h
	GL_LINE_SMOOTH_HINT     EQU 00C52h
	GL_POLYGON_SMOOTH_HINT  EQU 00C53h
	GL_FOG_HINT             EQU 00C54h
	GL_TEXTURE_GEN_S        EQU 00C60h
	GL_TEXTURE_GEN_T        EQU 00C61h
	GL_TEXTURE_GEN_R        EQU 00C62h
	GL_TEXTURE_GEN_Q        EQU 00C63h
	GL_PIXEL_MAP_I_TO_I     EQU 00C70h
	GL_PIXEL_MAP_S_TO_S     EQU 00C71h
	GL_PIXEL_MAP_I_TO_R     EQU 00C72h
	GL_PIXEL_MAP_I_TO_G     EQU 00C73h
	GL_PIXEL_MAP_I_TO_B     EQU 00C74h
	GL_PIXEL_MAP_I_TO_A     EQU 00C75h
	GL_PIXEL_MAP_R_TO_R     EQU 00C76h
	GL_PIXEL_MAP_G_TO_G     EQU 00C77h
	GL_PIXEL_MAP_B_TO_B     EQU 00C78h
	GL_PIXEL_MAP_A_TO_A     EQU 00C79h
	GL_PIXEL_MAP_I_TO_I_SIZE EQU 00CB0h
	GL_PIXEL_MAP_S_TO_S_SIZE EQU 00CB1h
	GL_PIXEL_MAP_I_TO_R_SIZE EQU 00CB2h
	GL_PIXEL_MAP_I_TO_G_SIZE EQU 00CB3h
	GL_PIXEL_MAP_I_TO_B_SIZE EQU 00CB4h
	GL_PIXEL_MAP_I_TO_A_SIZE EQU 00CB5h
	GL_PIXEL_MAP_R_TO_R_SIZE EQU 00CB6h
	GL_PIXEL_MAP_G_TO_G_SIZE EQU 00CB7h
	GL_PIXEL_MAP_B_TO_B_SIZE EQU 00CB8h
	GL_PIXEL_MAP_A_TO_A_SIZE EQU 00CB9h
	GL_UNPACK_SWAP_BYTES    EQU 00CF0h
	GL_UNPACK_LSB_FIRST     EQU 00CF1h
	GL_UNPACK_ROW_LENGTH    EQU 00CF2h
	GL_UNPACK_SKIP_ROWS     EQU 00CF3h
	GL_UNPACK_SKIP_PIXELS   EQU 00CF4h
	GL_UNPACK_ALIGNMENT     EQU 00CF5h
	GL_PACK_SWAP_BYTES      EQU 00D00h
	GL_PACK_LSB_FIRST       EQU 00D01h
	GL_PACK_ROW_LENGTH      EQU 00D02h
	GL_PACK_SKIP_ROWS       EQU 00D03h
	GL_PACK_SKIP_PIXELS     EQU 00D04h
	GL_PACK_ALIGNMENT       EQU 00D05h
	GL_MAP_COLOR            EQU 00D10h
	GL_MAP_STENCIL          EQU 00D11h
	GL_INDEX_SHIFT          EQU 00D12h
	GL_INDEX_OFFSET         EQU 00D13h
	GL_RED_SCALE            EQU 00D14h
	GL_RED_BIAS             EQU 00D15h
	GL_ZOOM_X               EQU 00D16h
	GL_ZOOM_Y               EQU 00D17h
	GL_GREEN_SCALE          EQU 00D18h
	GL_GREEN_BIAS           EQU 00D19h
	GL_BLUE_SCALE           EQU 00D1Ah
	GL_BLUE_BIAS            EQU 00D1Bh
	GL_ALPHA_SCALE          EQU 00D1Ch
	GL_ALPHA_BIAS           EQU 00D1Dh
	GL_DEPTH_SCALE          EQU 00D1Eh
	GL_DEPTH_BIAS           EQU 00D1Fh
	GL_MAX_EVAL_ORDER       EQU 00D30h
	GL_MAX_LIGHTS           EQU 00D31h
	GL_MAX_CLIP_PLANES      EQU 00D32h
	GL_MAX_TEXTURE_SIZE     EQU 00D33h
	GL_MAX_PIXEL_MAP_TABLE  EQU 00D34h
	GL_MAX_ATTRIB_STACK_DEPTH EQU 00D35h
	GL_MAX_MODELVIEW_STACK_DEPTH EQU 00D36h
	GL_MAX_NAME_STACK_DEPTH EQU 00D37h
	GL_MAX_PROJECTION_STACK_DEPTH EQU 00D38h
	GL_MAX_TEXTURE_STACK_DEPTH EQU 00D39h
	GL_MAX_VIEWPORT_DIMS    EQU 00D3Ah
	GL_MAX_CLIENT_ATTRIB_STACK_DEPTH EQU 00D3Bh
	GL_SUBPIXEL_BITS        EQU 00D50h
	GL_INDEX_BITS           EQU 00D51h
	GL_RED_BITS             EQU 00D52h
	GL_GREEN_BITS           EQU 00D53h
	GL_BLUE_BITS            EQU 00D54h
	GL_ALPHA_BITS           EQU 00D55h
	GL_DEPTH_BITS           EQU 00D56h
	GL_STENCIL_BITS         EQU 00D57h
	GL_ACCUM_RED_BITS       EQU 00D58h
	GL_ACCUM_GREEN_BITS     EQU 00D59h
	GL_ACCUM_BLUE_BITS      EQU 00D5Ah
	GL_ACCUM_ALPHA_BITS     EQU 00D5Bh
	GL_NAME_STACK_DEPTH     EQU 00D70h
	GL_AUTO_NORMAL          EQU 00D80h
	GL_MAP1_COLOR_4         EQU 00D90h
	GL_MAP1_INDEX           EQU 00D91h
	GL_MAP1_NORMAL          EQU 00D92h
	GL_MAP1_TEXTURE_COORD_1 EQU 00D93h
	GL_MAP1_TEXTURE_COORD_2 EQU 00D94h
	GL_MAP1_TEXTURE_COORD_3 EQU 00D95h
	GL_MAP1_TEXTURE_COORD_4 EQU 00D96h
	GL_MAP1_VERTEX_3        EQU 00D97h
	GL_MAP1_VERTEX_4        EQU 00D98h
	GL_MAP2_COLOR_4         EQU 00DB0h
	GL_MAP2_INDEX           EQU 00DB1h
	GL_MAP2_NORMAL          EQU 00DB2h
	GL_MAP2_TEXTURE_COORD_1 EQU 00DB3h
	GL_MAP2_TEXTURE_COORD_2 EQU 00DB4h
	GL_MAP2_TEXTURE_COORD_3 EQU 00DB5h
	GL_MAP2_TEXTURE_COORD_4 EQU 00DB6h
	GL_MAP2_VERTEX_3        EQU 00DB7h
	GL_MAP2_VERTEX_4        EQU 00DB8h
	GL_MAP1_GRID_DOMAIN     EQU 00DD0h
	GL_MAP1_GRID_SEGMENTS   EQU 00DD1h
	GL_MAP2_GRID_DOMAIN     EQU 00DD2h
	GL_MAP2_GRID_SEGMENTS   EQU 00DD3h
	GL_TEXTURE_1D           EQU 00DE0h
	GL_TEXTURE_2D           EQU 00DE1h
	GL_FEEDBACK_BUFFER_POINTER EQU 00DF0h
	GL_FEEDBACK_BUFFER_SIZE EQU 00DF1h
	GL_FEEDBACK_BUFFER_TYPE EQU 00DF2h
	GL_SELECTION_BUFFER_POINTER EQU 00DF3h
	GL_SELECTION_BUFFER_SIZE EQU 00DF4h
	GL_TEXTURE_WIDTH        EQU 01000h
	GL_TEXTURE_HEIGHT       EQU 01001h
	GL_TEXTURE_INTERNAL_FORMAT EQU 01003h
	GL_TEXTURE_BORDER_COLOR EQU 01004h
	GL_TEXTURE_BORDER       EQU 01005h
	GL_DONT_CARE            EQU 01100h
	GL_FASTEST              EQU 01101h
	GL_NICEST               EQU 01102h
	GL_LIGHT0               EQU 04000h
	GL_LIGHT1               EQU 04001h
	GL_LIGHT2               EQU 04002h
	GL_LIGHT3               EQU 04003h
	GL_LIGHT4               EQU 04004h
	GL_LIGHT5               EQU 04005h
	GL_LIGHT6               EQU 04006h
	GL_LIGHT7               EQU 04007h
	GL_AMBIENT              EQU 01200h
	GL_DIFFUSE              EQU 01201h
	GL_SPECULAR             EQU 01202h
	GL_POSITION             EQU 01203h
	GL_SPOT_DIRECTION       EQU 01204h
	GL_SPOT_EXPONENT        EQU 01205h
	GL_SPOT_CUTOFF          EQU 01206h
	GL_CONSTANT_ATTENUATION EQU 01207h
	GL_LINEAR_ATTENUATION   EQU 01208h
	GL_QUADRATIC_ATTENUATION EQU 01209h
	GL_COMPILE              EQU 01300h
	GL_COMPILE_AND_EXECUTE  EQU 01301h
	GL_CLEAR                EQU 01500h
	GL_AND                  EQU 01501h
	GL_AND_REVERSE          EQU 01502h
	GL_COPY                 EQU 01503h
	GL_AND_INVERTED         EQU 01504h
	GL_NOOP                 EQU 01505h
	GL_XOR                  EQU 01506h
	GL_OR                   EQU 01507h
	GL_NOR                  EQU 01508h
	GL_EQUIV                EQU 01509h
	GL_INVERT               EQU 0150Ah
	GL_OR_REVERSE           EQU 0150Bh
	GL_COPY_INVERTED        EQU 0150Ch
	GL_OR_INVERTED          EQU 0150Dh
	GL_NAND                 EQU 0150Eh
	GL_SET                  EQU 0150Fh
	GL_EMISSION             EQU 01600h
	GL_SHININESS            EQU 01601h
	GL_AMBIENT_AND_DIFFUSE  EQU 01602h
	GL_COLOR_INDEXES        EQU 01603h
	GL_MODELVIEW            EQU 01700h
	GL_PROJECTION           EQU 01701h
	GL_TEXTURE              EQU 01702h
	GL_COLOR                EQU 01800h
	GL_DEPTH                EQU 01801h
	GL_STENCIL              EQU 01802h
	GL_COLOR_INDEX          EQU 01900h
	GL_STENCIL_INDEX        EQU 01901h
	GL_DEPTH_COMPONENT      EQU 01902h
	GL_RED                  EQU 01903h
	GL_GREEN                EQU 01904h
	GL_BLUE                 EQU 01905h
	GL_ALPHA                EQU 01906h
	GL_RGB                  EQU 01907h
	GL_RGBA                 EQU 01908h
	GL_LUMINANCE            EQU 01909h
	GL_LUMINANCE_ALPHA      EQU 0190Ah
	GL_BITMAP               EQU 01A00h
	GL_POINT                EQU 01B00h
	GL_LINE                 EQU 01B01h
	GL_FILL                 EQU 01B02h
	GL_RENDER               EQU 01C00h
	GL_FEEDBACK             EQU 01C01h
	GL_SELECT               EQU 01C02h
	GL_FLAT                 EQU 01D00h
	GL_SMOOTH               EQU 01D01h
	GL_KEEP                 EQU 01E00h
	GL_REPLACE              EQU 01E01h
	GL_INCR                 EQU 01E02h
	GL_DECR                 EQU 01E03h
	GL_VENDOR               EQU 01F00h
	GL_RENDERER             EQU 01F01h
	GL_VERSION              EQU 01F02h
	GL_EXTENSIONS           EQU 01F03h
	GL_S                    EQU 02000h
	GL_T                    EQU 02001h
	GL_R                    EQU 02002h
	GL_Q                    EQU 02003h
	GL_MODULATE             EQU 02100h
	GL_DECAL                EQU 02101h
	GL_TEXTURE_ENV_MODE     EQU 02200h
	GL_TEXTURE_ENV_COLOR    EQU 02201h
	GL_TEXTURE_ENV          EQU 02300h
	GL_EYE_LINEAR           EQU 02400h
	GL_OBJECT_LINEAR        EQU 02401h
	GL_SPHERE_MAP           EQU 02402h
	GL_TEXTURE_GEN_MODE     EQU 02500h
	GL_OBJECT_PLANE         EQU 02501h
	GL_EYE_PLANE            EQU 02502h
	GL_NEAREST              EQU 02600h
	GL_LINEAR               EQU 02601h
	GL_NEAREST_MIPMAP_NEAREST EQU 02700h
	GL_LINEAR_MIPMAP_NEAREST EQU 02701h
	GL_NEAREST_MIPMAP_LINEAR EQU 02702h
	GL_LINEAR_MIPMAP_LINEAR EQU 02703h
	GL_TEXTURE_MAG_FILTER   EQU 02800h
	GL_TEXTURE_MIN_FILTER   EQU 02801h
	GL_TEXTURE_WRAP_S       EQU 02802h
	GL_TEXTURE_WRAP_T       EQU 02803h
	GL_CLAMP                EQU 02900h
	GL_REPEAT               EQU 02901h
	GL_CLIENT_PIXEL_STORE_BIT EQU 000000001h
	GL_CLIENT_VERTEX_ARRAY_BIT EQU 000000002h
	GL_CLIENT_ALL_ATTRIB_BITS EQU 0ffffffffh
	GL_POLYGON_OFFSET_FACTOR EQU 08038h
	GL_POLYGON_OFFSET_UNITS EQU 02A00h
	GL_POLYGON_OFFSET_POINT EQU 02A01h
	GL_POLYGON_OFFSET_LINE  EQU 02A02h
	GL_POLYGON_OFFSET_FILL  EQU 08037h
	GL_ALPHA4               EQU 0803Bh
	GL_ALPHA8               EQU 0803Ch
	GL_ALPHA12              EQU 0803Dh
	GL_ALPHA16              EQU 0803Eh
	GL_LUMINANCE4           EQU 0803Fh
	GL_LUMINANCE8           EQU 08040h
	GL_LUMINANCE12          EQU 08041h
	GL_LUMINANCE16          EQU 08042h
	GL_LUMINANCE4_ALPHA4    EQU 08043h
	GL_LUMINANCE6_ALPHA2    EQU 08044h
	GL_LUMINANCE8_ALPHA8    EQU 08045h
	GL_LUMINANCE12_ALPHA4   EQU 08046h
	GL_LUMINANCE12_ALPHA12  EQU 08047h
	GL_LUMINANCE16_ALPHA16  EQU 08048h
	GL_INTENSITY            EQU 08049h
	GL_INTENSITY4           EQU 0804Ah
	GL_INTENSITY8           EQU 0804Bh
	GL_INTENSITY12          EQU 0804Ch
	GL_INTENSITY16          EQU 0804Dh
	GL_R3_G3_B2             EQU 02A10h
	GL_RGB4                 EQU 0804Fh
	GL_RGB5                 EQU 08050h
	GL_RGB8                 EQU 08051h
	GL_RGB10                EQU 08052h
	GL_RGB12                EQU 08053h
	GL_RGB16                EQU 08054h
	GL_RGBA2                EQU 08055h
	GL_RGBA4                EQU 08056h
	GL_RGB5_A1              EQU 08057h
	GL_RGBA8                EQU 08058h
	GL_RGB10_A2             EQU 08059h
	GL_RGBA12               EQU 0805Ah
	GL_RGBA16               EQU 0805Bh
	GL_TEXTURE_RED_SIZE     EQU 0805Ch
	GL_TEXTURE_GREEN_SIZE   EQU 0805Dh
	GL_TEXTURE_BLUE_SIZE    EQU 0805Eh
	GL_TEXTURE_ALPHA_SIZE   EQU 0805Fh
	GL_TEXTURE_LUMINANCE_SIZE EQU 08060h
	GL_TEXTURE_INTENSITY_SIZE EQU 08061h
	GL_PROXY_TEXTURE_1D     EQU 08063h
	GL_PROXY_TEXTURE_2D     EQU 08064h
	GL_TEXTURE_PRIORITY     EQU 08066h
	GL_TEXTURE_RESIDENT     EQU 08067h
	GL_TEXTURE_BINDING_1D   EQU 08068h
	GL_TEXTURE_BINDING_2D   EQU 08069h
	GL_VERTEX_ARRAY         EQU 08074h
	GL_NORMAL_ARRAY         EQU 08075h
	GL_COLOR_ARRAY          EQU 08076h
	GL_INDEX_ARRAY          EQU 08077h
	GL_TEXTURE_COORD_ARRAY  EQU 08078h
	GL_EDGE_FLAG_ARRAY      EQU 08079h
	GL_VERTEX_ARRAY_SIZE    EQU 0807Ah
	GL_VERTEX_ARRAY_TYPE    EQU 0807Bh
	GL_VERTEX_ARRAY_STRIDE  EQU 0807Ch
	GL_NORMAL_ARRAY_TYPE    EQU 0807Eh
	GL_NORMAL_ARRAY_STRIDE  EQU 0807Fh
	GL_COLOR_ARRAY_SIZE     EQU 08081h
	GL_COLOR_ARRAY_TYPE     EQU 08082h
	GL_COLOR_ARRAY_STRIDE   EQU 08083h
	GL_INDEX_ARRAY_TYPE     EQU 08085h
	GL_INDEX_ARRAY_STRIDE   EQU 08086h
	GL_TEXTURE_COORD_ARRAY_SIZE EQU 08088h
	GL_TEXTURE_COORD_ARRAY_TYPE EQU 08089h
	GL_TEXTURE_COORD_ARRAY_STRIDE EQU 0808Ah
	GL_EDGE_FLAG_ARRAY_STRIDE EQU 0808Ch
	GL_VERTEX_ARRAY_POINTER EQU 0808Eh
	GL_NORMAL_ARRAY_POINTER EQU 0808Fh
	GL_COLOR_ARRAY_POINTER  EQU 08090h
	GL_INDEX_ARRAY_POINTER  EQU 08091h
	GL_TEXTURE_COORD_ARRAY_POINTER EQU 08092h
	GL_EDGE_FLAG_ARRAY_POINTER EQU 08093h
	GL_V2F                  EQU 02A20h
	GL_V3F                  EQU 02A21h
	GL_C4UB_V2F             EQU 02A22h
	GL_C4UB_V3F             EQU 02A23h
	GL_C3F_V3F              EQU 02A24h
	GL_N3F_V3F              EQU 02A25h
	GL_C4F_N3F_V3F          EQU 02A26h
	GL_T2F_V3F              EQU 02A27h
	GL_T4F_V4F              EQU 02A28h
	GL_T2F_C4UB_V3F         EQU 02A29h
	GL_T2F_C3F_V3F          EQU 02A2Ah
	GL_T2F_N3F_V3F          EQU 02A2Bh
	GL_T2F_C4F_N3F_V3F      EQU 02A2Ch
	GL_T4F_C4F_N3F_V4F      EQU 02A2Dh
	GL_EXT_vertex_array     equ 1
	GL_EXT_bgra             equ 1
	GL_EXT_paletted_texture equ 1
	GL_WIN_swap_hint        equ 1
	GL_WIN_draw_range_elements equ 1
	GL_VERTEX_ARRAY_EXT     EQU 08074h
	GL_NORMAL_ARRAY_EXT     EQU 08075h
	GL_COLOR_ARRAY_EXT      EQU 08076h
	GL_INDEX_ARRAY_EXT      EQU 08077h
	GL_TEXTURE_COORD_ARRAY_EXT EQU 08078h
	GL_EDGE_FLAG_ARRAY_EXT  EQU 08079h
	GL_VERTEX_ARRAY_SIZE_EXT EQU 0807Ah
	GL_VERTEX_ARRAY_TYPE_EXT EQU 0807Bh
	GL_VERTEX_ARRAY_STRIDE_EXT EQU 0807Ch
	GL_VERTEX_ARRAY_COUNT_EXT EQU 0807Dh
	GL_NORMAL_ARRAY_TYPE_EXT EQU 0807Eh
	GL_NORMAL_ARRAY_STRIDE_EXT EQU 0807Fh
	GL_NORMAL_ARRAY_COUNT_EXT EQU 08080h
	GL_COLOR_ARRAY_SIZE_EXT EQU 08081h
	GL_COLOR_ARRAY_TYPE_EXT EQU 08082h
	GL_COLOR_ARRAY_STRIDE_EXT EQU 08083h
	GL_COLOR_ARRAY_COUNT_EXT EQU 08084h
	GL_INDEX_ARRAY_TYPE_EXT EQU 08085h
	GL_INDEX_ARRAY_STRIDE_EXT EQU 08086h
	GL_INDEX_ARRAY_COUNT_EXT EQU 08087h
	GL_TEXTURE_COORD_ARRAY_SIZE_EXT EQU 08088h
	GL_TEXTURE_COORD_ARRAY_TYPE_EXT EQU 08089h
	GL_TEXTURE_COORD_ARRAY_STRIDE_EXT EQU 0808Ah
	GL_TEXTURE_COORD_ARRAY_COUNT_EXT EQU 0808Bh
	GL_EDGE_FLAG_ARRAY_STRIDE_EXT EQU 0808Ch
	GL_EDGE_FLAG_ARRAY_COUNT_EXT EQU 0808Dh
	GL_VERTEX_ARRAY_POINTER_EXT EQU 0808Eh
	GL_NORMAL_ARRAY_POINTER_EXT EQU 0808Fh
	GL_COLOR_ARRAY_POINTER_EXT EQU 08090h
	GL_INDEX_ARRAY_POINTER_EXT EQU 08091h
	GL_TEXTURE_COORD_ARRAY_POINTER_EXT EQU 08092h
	GL_EDGE_FLAG_ARRAY_POINTER_EXT EQU 08093h
	GL_DOUBLE_EXT           equ GL_DOUBLE
	GL_BGR_EXT              EQU 080E0h
	GL_BGRA_EXT             EQU 080E1h
	GL_COLOR_TABLE_FORMAT_EXT EQU 080D8h
	GL_COLOR_TABLE_WIDTH_EXT EQU 080D9h
	GL_COLOR_TABLE_RED_SIZE_EXT EQU 080DAh
	GL_COLOR_TABLE_GREEN_SIZE_EXT EQU 080DBh
	GL_COLOR_TABLE_BLUE_SIZE_EXT EQU 080DCh
	GL_COLOR_TABLE_ALPHA_SIZE_EXT EQU 080DDh
	GL_COLOR_TABLE_LUMINANCE_SIZE_EXT EQU 080DEh
	GL_COLOR_TABLE_INTENSITY_SIZE_EXT EQU 080DFh
	GL_COLOR_INDEX1_EXT     EQU 080E2h
	GL_COLOR_INDEX2_EXT     EQU 080E3h
	GL_COLOR_INDEX4_EXT     EQU 080E4h
	GL_COLOR_INDEX8_EXT     EQU 080E5h
	GL_COLOR_INDEX12_EXT    EQU 080E6h
	GL_COLOR_INDEX16_EXT    EQU 080E7h
	GL_MAX_ELEMENTS_VERTICES_WIN EQU 080E8h
	GL_MAX_ELEMENTS_INDICES_WIN EQU 080E9h
	GL_PHONG_WIN            EQU 080EAh
	GL_PHONG_HINT_WIN       EQU 080EBh
	GL_FOG_SPECULAR_TEXTURE_WIN EQU 080ECh
	GL_LOGIC_OP             equ GL_INDEX_LOGIC_OP
	GL_TEXTURE_COMPONENTS   equ GL_TEXTURE_INTERNAL_FORMAT

	glAccum				PROTO	:GLenum,:GLfloat
	glAlphaFunc				PROTO	:GLenum,:GLclampf
	glAreTexturesResident				PROTO	:GLsizei,:ptr GLuint,:ptr GLboolean
	glArrayElement				PROTO	:GLint
	glBegin				PROTO	:GLenum
	glBindTexture				PROTO	:GLenum,:GLuint
	glBitmap				PROTO	:GLsizei,:GLsizei,:GLfloat,:GLfloat,:GLfloat,:GLfloat,:ptr GLubyte
	glBlendFunc				PROTO	:GLenum,:GLenum
	glCallList				PROTO	:GLuint
	glCallLists				PROTO	:GLsizei,:GLenum,:ptr GLvoid
	glClear				PROTO	:GLbitfield
	glClearAccum				PROTO	:GLfloat,:GLfloat,:GLfloat,:GLfloat
	glClearColor				PROTO	:GLclampf,:GLclampf,:GLclampf,:GLclampf
	glClearDepth				PROTO	:GLclampd
	glClearIndex				PROTO	:GLfloat
	glClearStencil				PROTO	:GLint
	glClipPlane				PROTO	:GLenum,:ptr GLdouble
	glColor3b				PROTO	:GLbyte,:GLbyte,:GLbyte
	glColor3bv				PROTO	:ptr GLbyte
	glColor3d				PROTO	:GLdouble,:GLdouble,:GLdouble
	glColor3dv				PROTO	:ptr GLdouble
	glColor3f				PROTO	:GLfloat,:GLfloat,:GLfloat
	glColor3fv				PROTO	:ptr GLfloat
	glColor3i				PROTO	:GLint,:GLint,:GLint
	glColor3iv				PROTO	:ptr GLint
	glColor3s				PROTO	:GLshort,:GLshort,:GLshort
	glColor3sv				PROTO	:ptr GLshort
	glColor3ub				PROTO	:GLubyte,:GLubyte,:GLubyte
	glColor3ubv				PROTO	:ptr GLubyte
	glColor3ui				PROTO	:GLuint,:GLuint,:GLuint
	glColor3uiv				PROTO	:ptr GLuint
	glColor3us				PROTO	:GLushort,:GLushort,:GLushort
	glColor3usv				PROTO	:ptr GLushort
	glColor4b				PROTO	:GLbyte,:GLbyte,:GLbyte,:GLbyte
	glColor4bv				PROTO	:ptr GLbyte
	glColor4d				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble
	glColor4dv				PROTO	:ptr GLdouble
	glColor4f				PROTO	:GLfloat,:GLfloat,:GLfloat,:GLfloat
	glColor4fv				PROTO	:ptr GLfloat
	glColor4i				PROTO	:GLint,:GLint,:GLint,:GLint
	glColor4iv				PROTO	:ptr GLint
	glColor4s				PROTO	:GLshort,:GLshort,:GLshort,:GLshort
	glColor4sv				PROTO	:ptr GLshort
	glColor4ub				PROTO	:GLubyte,:GLubyte,:GLubyte,:GLubyte
	glColor4ubv				PROTO	:ptr GLubyte
	glColor4ui				PROTO	:GLuint,:GLuint,:GLuint,:GLuint
	glColor4uiv				PROTO	:ptr GLuint
	glColor4us				PROTO	:GLushort,:GLushort,:GLushort,:GLushort
	glColor4usv				PROTO	:ptr GLushort
	glColorMask				PROTO	:GLboolean,:GLboolean,:GLboolean,:GLboolean
	glColorMaterial				PROTO	:GLenum,:GLenum
	glColorPointer				PROTO	:GLint,:GLenum,:GLsizei,:ptr GLvoid
	glCopyPixels				PROTO	:GLint,:GLint,:GLsizei,:GLsizei,:GLenum
	glCopyTexImage1D				PROTO	:GLenum,:GLint,:GLenum,:GLint,:GLint,:GLsizei,:GLint
	glCopyTexImage2D				PROTO	:GLenum,:GLint,:GLenum,:GLint,:GLint,:GLsizei,:GLsizei,:GLint
	glCopyTexSubImage1D				PROTO	:GLenum,:GLint,:GLint,:GLint,:GLint,:GLsizei
	glCopyTexSubImage2D				PROTO	:GLenum,:GLint,:GLint,:GLint,:GLint,:GLint,:GLsizei,:GLsizei
	glCullFace				PROTO	:GLenum
	glDeleteLists				PROTO	:GLuint,:GLsizei
	glDeleteTextures				PROTO	:GLsizei,:ptr GLuint
	glDepthFunc				PROTO	:GLenum
	glDepthMask				PROTO	:GLboolean
	glDepthRange				PROTO	:GLclampd,:GLclampd
	glDisable				PROTO	:GLenum
	glDisableClientState				PROTO	:GLenum
	glDrawArrays				PROTO	:GLenum,:GLint,:GLsizei
	glDrawBuffer				PROTO	:GLenum
	glDrawElements				PROTO	:GLenum,:GLsizei,:GLenum,:ptr GLvoid
	glDrawPixels				PROTO	:GLsizei,:GLsizei,:GLenum,:GLenum,:ptr GLvoid
	glEdgeFlag				PROTO	:GLboolean
	glEdgeFlagPointer				PROTO	:GLsizei,:ptr GLvoid
	glEdgeFlagv				PROTO	:ptr GLboolean
	glEnable				PROTO	:GLenum
	glEnableClientState				PROTO	:GLenum
	glEnd				PROTO	
	glEndList				PROTO	
	glEvalCoord1d				PROTO	:GLdouble
	glEvalCoord1dv				PROTO	:ptr GLdouble
	glEvalCoord1f				PROTO	:GLfloat
	glEvalCoord1fv				PROTO	:ptr GLfloat
	glEvalCoord2d				PROTO	:GLdouble,:GLdouble
	glEvalCoord2dv				PROTO	:ptr GLdouble
	glEvalCoord2f				PROTO	:GLfloat,:GLfloat
	glEvalCoord2fv				PROTO	:ptr GLfloat
	glEvalMesh1				PROTO	:GLenum,:GLint,:GLint
	glEvalMesh2				PROTO	:GLenum,:GLint,:GLint,:GLint,:GLint
	glEvalPoint1				PROTO	:GLint
	glEvalPoint2				PROTO	:GLint,:GLint
	glFeedbackBuffer				PROTO	:GLsizei,:GLenum,:ptr GLfloat
	glFinish				PROTO	
	glFlush				PROTO	
	glFogf				PROTO	:GLenum,:GLfloat
	glFogfv				PROTO	:GLenum,:ptr GLfloat
	glFogi				PROTO	:GLenum,:GLint
	glFogiv				PROTO	:GLenum,:ptr GLint
	glFrontFace				PROTO	:GLenum
	glFrustum				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble,:GLdouble,:GLdouble
	glGenLists				PROTO	:GLsizei
	glGenTextures				PROTO	:GLsizei,:ptr GLuint
	glGetBooleanv				PROTO	:GLenum,:ptr GLboolean
	glGetClipPlane				PROTO	:GLenum,:ptr GLdouble
	glGetDoublev				PROTO	:GLenum,:ptr GLdouble
	glGetError				PROTO	
	glGetFloatv				PROTO	:GLenum,:ptr GLfloat
	glGetIntegerv				PROTO	:GLenum,:ptr GLint
	glGetLightfv				PROTO	:GLenum,:GLenum,:ptr GLfloat
	glGetLightiv				PROTO	:GLenum,:GLenum,:ptr GLint
	glGetMapdv				PROTO	:GLenum,:GLenum,:ptr GLdouble
	glGetMapfv				PROTO	:GLenum,:GLenum,:ptr GLfloat
	glGetMapiv				PROTO	:GLenum,:GLenum,:ptr GLint
	glGetMaterialfv				PROTO	:GLenum,:GLenum,:ptr GLfloat
	glGetMaterialiv				PROTO	:GLenum,:GLenum,:ptr GLint
	glGetPixelMapfv				PROTO	:GLenum,:ptr GLfloat
	glGetPixelMapuiv				PROTO	:GLenum,:ptr GLuint
	glGetPixelMapusv				PROTO	:GLenum,:ptr GLushort
	glGetPointerv				PROTO	:GLenum,:ptr GLvoid
	glGetPolygonStipple				PROTO	:ptr GLubyte
	glGetString				PROTO	:GLenum
	glGetTexEnvfv				PROTO	:GLenum,:GLenum,:ptr GLfloat
	glGetTexEnviv				PROTO	:GLenum,:GLenum,:ptr GLint
	glGetTexGendv				PROTO	:GLenum,:GLenum,:ptr GLdouble
	glGetTexGenfv				PROTO	:GLenum,:GLenum,:ptr GLfloat
	glGetTexGeniv				PROTO	:GLenum,:GLenum,:ptr GLint
	glGetTexImage				PROTO	:GLenum,:GLint,:GLenum,:GLenum,:ptr GLvoid
	glGetTexLevelParameterfv				PROTO	:GLenum,:GLint,:GLenum,:ptr GLfloat
	glGetTexLevelParameteriv				PROTO	:GLenum,:GLint,:GLenum,:ptr GLint
	glGetTexParameterfv				PROTO	:GLenum,:GLenum,:ptr GLfloat
	glGetTexParameteriv				PROTO	:GLenum,:GLenum,:ptr GLint
	glHint				PROTO	:GLenum,:GLenum
	glIndexMask				PROTO	:GLuint
	glIndexPointer				PROTO	:GLenum,:GLsizei,:ptr GLvoid
	glIndexd				PROTO	:GLdouble
	glIndexdv				PROTO	:ptr GLdouble
	glIndexf				PROTO	:GLfloat
	glIndexfv				PROTO	:ptr GLfloat
	glIndexi				PROTO	:GLint
	glIndexiv				PROTO	:ptr GLint
	glIndexs				PROTO	:GLshort
	glIndexsv				PROTO	:ptr GLshort
	glIndexub				PROTO	:GLubyte
	glIndexubv				PROTO	:ptr GLubyte
	glInitNames				PROTO	
	glInterleavedArrays				PROTO	:GLenum,:GLsizei,:ptr GLvoid
	glIsEnabled				PROTO	:GLenum
	glIsList				PROTO	:GLuint
	glIsTexture				PROTO	:GLuint
	glLightModelf				PROTO	:GLenum,:GLfloat
	glLightModelfv				PROTO	:GLenum,:ptr GLfloat
	glLightModeli				PROTO	:GLenum,:GLint
	glLightModeliv				PROTO	:GLenum,:ptr GLint
	glLightf				PROTO	:GLenum,:GLenum,:GLfloat
	glLightfv				PROTO	:VARARG;GLenum,:GLenum,:ptr GLfloat
	glLighti				PROTO	:GLenum,:GLenum,:GLint
	glLightiv				PROTO	:GLenum,:GLenum,:ptr GLint
	glLineStipple				PROTO	:GLint,:GLushort
	glLineWidth				PROTO	:GLfloat
	glListBase				PROTO	:GLuint
	glLoadIdentity				PROTO	
	glLoadMatrixd				PROTO	:ptr GLdouble
	glLoadMatrixf				PROTO	:ptr GLfloat
	glLoadName				PROTO	:GLuint
	glLogicOp				PROTO	:GLenum
	glMap1d				PROTO	:GLenum,:GLdouble,:GLdouble,:GLint,:GLint,:ptr GLdouble
	glMap1f				PROTO	:GLenum,:GLfloat,:GLfloat,:GLint,:GLint,:ptr GLfloat
	glMap2d				PROTO	:GLenum,:GLdouble,:GLdouble,:GLint,:GLint,:GLdouble,:GLdouble,:GLint,:GLint,:ptr GLdouble
	glMap2f				PROTO	:GLenum,:GLfloat,:GLfloat,:GLint,:GLint,:GLfloat,:GLfloat,:GLint,:GLint,:ptr GLfloat
	glMapGrid1d				PROTO	:GLint,:GLdouble,:GLdouble
	glMapGrid1f				PROTO	:GLint,:GLfloat,:GLfloat
	glMapGrid2d				PROTO	:GLint,:GLdouble,:GLdouble,:GLint,:GLdouble,:GLdouble
	glMapGrid2f				PROTO	:GLint,:GLfloat,:GLfloat,:GLint,:GLfloat,:GLfloat
	glMaterialf				PROTO	:GLenum,:GLenum,:GLfloat
	glMaterialfv				PROTO	:GLenum,:GLenum,:ptr GLfloat
	glMateriali				PROTO	:GLenum,:GLenum,:GLint
	glMaterialiv				PROTO	:GLenum,:GLenum,:ptr GLint
	glMatrixMode				PROTO	:GLenum
	glMultMatrixd				PROTO	:ptr GLdouble
	glMultMatrixf				PROTO	:ptr GLfloat
	glNewList				PROTO	:GLuint,:GLenum
	glNormal3b				PROTO	:GLbyte,:GLbyte,:GLbyte
	glNormal3bv				PROTO	:ptr GLbyte
	glNormal3d				PROTO	:GLdouble,:GLdouble,:GLdouble
	glNormal3dv				PROTO	:ptr GLdouble
	glNormal3f				PROTO	:GLfloat,:GLfloat,:GLfloat
	glNormal3fv				PROTO	:ptr GLfloat
	glNormal3i				PROTO	:GLint,:GLint,:GLint
	glNormal3iv				PROTO	:ptr GLint
	glNormal3s				PROTO	:GLshort,:GLshort,:GLshort
	glNormal3sv				PROTO	:ptr GLshort
	glNormalPointer				PROTO	:GLenum,:GLsizei,:ptr GLvoid
	glOrtho				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble,:GLdouble,:GLdouble
	glPassThrough				PROTO	:GLfloat
	glPixelMapfv				PROTO	:GLenum,:GLsizei,:ptr GLfloat
	glPixelMapuiv				PROTO	:GLenum,:GLsizei,:ptr GLuint
	glPixelMapusv				PROTO	:GLenum,:GLsizei,:ptr GLushort
	glPixelStoref				PROTO	:GLenum,:GLfloat
	glPixelStorei				PROTO	:GLenum,:GLint
	glPixelTransferf				PROTO	:GLenum,:GLfloat
	glPixelTransferi				PROTO	:GLenum,:GLint
	glPixelZoom				PROTO	:GLfloat,:GLfloat
	glPointSize				PROTO	:GLfloat
	glPolygonMode				PROTO	:GLenum,:GLenum
	glPolygonOffset				PROTO	:GLfloat,:GLfloat
	glPolygonStipple				PROTO	:ptr GLubyte
	glPopAttrib				PROTO	
	glPopClientAttrib				PROTO	
	glPopMatrix				PROTO	
	glPopName				PROTO	
	glPrioritizeTextures				PROTO	:GLsizei,:ptr GLuint,:ptr GLclampf
	glPushAttrib				PROTO	:GLbitfield
	glPushClientAttrib				PROTO	:GLbitfield
	glPushMatrix				PROTO	
	glPushName				PROTO	:GLuint
	glRasterPos2d				PROTO	:GLdouble,:GLdouble
	glRasterPos2dv				PROTO	:ptr GLdouble
	glRasterPos2f				PROTO	:GLfloat,:GLfloat
	glRasterPos2fv				PROTO	:ptr GLfloat
	glRasterPos2i				PROTO	:GLint,:GLint
	glRasterPos2iv				PROTO	:ptr GLint
	glRasterPos2s				PROTO	:GLshort,:GLshort
	glRasterPos2sv				PROTO	:ptr GLshort
	glRasterPos3d				PROTO	:GLdouble,:GLdouble,:GLdouble
	glRasterPos3dv				PROTO	:ptr GLdouble
	glRasterPos3f				PROTO	:GLfloat,:GLfloat,:GLfloat
	glRasterPos3fv				PROTO	:ptr GLfloat
	glRasterPos3i				PROTO	:GLint,:GLint,:GLint
	glRasterPos3iv				PROTO	:ptr GLint
	glRasterPos3s				PROTO	:GLshort,:GLshort,:GLshort
	glRasterPos3sv				PROTO	:ptr GLshort
	glRasterPos4d				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble
	glRasterPos4dv				PROTO	:ptr GLdouble
	glRasterPos4f				PROTO	:GLfloat,:GLfloat,:GLfloat,:GLfloat
	glRasterPos4fv				PROTO	:ptr GLfloat
	glRasterPos4i				PROTO	:GLint,:GLint,:GLint,:GLint
	glRasterPos4iv				PROTO	:ptr GLint
	glRasterPos4s				PROTO	:GLshort,:GLshort,:GLshort,:GLshort
	glRasterPos4sv				PROTO	:ptr GLshort
	glReadBuffer				PROTO	:GLenum
	glReadPixels				PROTO	:GLint,:GLint,:GLsizei,:GLsizei,:GLenum,:GLenum,:ptr GLvoid
	glRectd				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble
	glRectdv				PROTO	:ptr GLdouble,:ptr GLdouble
	glRectf				PROTO	:GLfloat,:GLfloat,:GLfloat,:GLfloat
	glRectfv				PROTO	:ptr GLfloat,:ptr GLfloat
	glRecti				PROTO	:GLint,:GLint,:GLint,:GLint
	glRectiv				PROTO	:ptr GLint,:ptr GLint
	glRects				PROTO	:GLshort,:GLshort,:GLshort,:GLshort
	glRectsv				PROTO	:ptr GLshort,:ptr GLshort
	glRenderMode				PROTO	:GLenum
	glRotated				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble
	glRotatef				PROTO	:GLfloat,:GLfloat,:GLfloat,:GLfloat
	glScaled				PROTO	:GLdouble,:GLdouble,:GLdouble
	glScalef				PROTO	:GLfloat,:GLfloat,:GLfloat
	glScissor				PROTO	:GLint,:GLint,:GLsizei,:GLsizei
	glSelectBuffer				PROTO	:GLsizei,:ptr GLuint
	glShadeModel				PROTO	:GLenum
	glStencilFunc				PROTO	:GLenum,:GLint,:GLuint
	glStencilMask				PROTO	:GLuint
	glStencilOp				PROTO	:GLenum,:GLenum,:GLenum
	glTexCoord1d				PROTO	:GLdouble
	glTexCoord1dv				PROTO	:ptr GLdouble
	glTexCoord1f				PROTO	:GLfloat
	glTexCoord1fv				PROTO	:ptr GLfloat
	glTexCoord1i				PROTO	:GLint
	glTexCoord1iv				PROTO	:ptr GLint
	glTexCoord1s				PROTO	:GLshort
	glTexCoord1sv				PROTO	:ptr GLshort
	glTexCoord2d				PROTO	:GLdouble,:GLdouble
	glTexCoord2dv				PROTO	:ptr GLdouble
	glTexCoord2f				PROTO	:GLfloat,:GLfloat
	glTexCoord2fv				PROTO	:ptr GLfloat
	glTexCoord2i				PROTO	:GLint,:GLint
	glTexCoord2iv				PROTO	:ptr GLint
	glTexCoord2s				PROTO	:GLshort,:GLshort
	glTexCoord2sv				PROTO	:ptr GLshort
	glTexCoord3d				PROTO	:GLdouble,:GLdouble,:GLdouble
	glTexCoord3dv				PROTO	:ptr GLdouble
	glTexCoord3f				PROTO	:GLfloat,:GLfloat,:GLfloat
	glTexCoord3fv				PROTO	:ptr GLfloat
	glTexCoord3i				PROTO	:GLint,:GLint,:GLint
	glTexCoord3iv				PROTO	:ptr GLint
	glTexCoord3s				PROTO	:GLshort,:GLshort,:GLshort
	glTexCoord3sv				PROTO	:ptr GLshort
	glTexCoord4d				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble
	glTexCoord4dv				PROTO	:ptr GLdouble
	glTexCoord4f				PROTO	:GLfloat,:GLfloat,:GLfloat,:GLfloat
	glTexCoord4fv				PROTO	:ptr GLfloat
	glTexCoord4i				PROTO	:GLint,:GLint,:GLint,:GLint
	glTexCoord4iv				PROTO	:ptr GLint
	glTexCoord4s				PROTO	:GLshort,:GLshort,:GLshort,:GLshort
	glTexCoord4sv				PROTO	:ptr GLshort
	glTexCoordPointer				PROTO	:GLint,:GLenum,:GLsizei,:ptr GLvoid
	glTexEnvf				PROTO	:GLenum,:GLenum,:GLfloat
	glTexEnvfv				PROTO	:GLenum,:GLenum,:ptr GLfloat
	glTexEnvi				PROTO	:GLenum,:GLenum,:GLint
	glTexEnviv				PROTO	:GLenum,:GLenum,:ptr GLint
	glTexGend				PROTO	:GLenum,:GLenum,:GLdouble
	glTexGendv				PROTO	:GLenum,:GLenum,:ptr GLdouble
	glTexGenf				PROTO	:GLenum,:GLenum,:GLfloat
	glTexGenfv				PROTO	:GLenum,:GLenum,:ptr GLfloat
	glTexGeni				PROTO	:GLenum,:GLenum,:GLint
	glTexGeniv				PROTO	:GLenum,:GLenum,:ptr GLint
	glTexImage1D				PROTO	:GLenum,:GLint,:GLint,:GLsizei,:GLint,:GLenum,:GLenum,:ptr GLvoid
	glTexImage2D				PROTO	:GLenum,:GLint,:GLint,:GLsizei,:GLsizei,:GLint,:GLenum,:GLenum,:ptr GLvoid
	glTexParameterf				PROTO	:GLenum,:GLenum,:GLfloat
	glTexParameterfv				PROTO	:GLenum,:GLenum,:ptr GLfloat
	glTexParameteri				PROTO	:GLenum,:GLenum,:GLint
	glTexParameteriv				PROTO	:GLenum,:GLenum,:ptr GLint
	glTexSubImage1D				PROTO	:GLenum,:GLint,:GLint,:GLsizei,:GLenum,:GLenum,:ptr GLvoid
	glTexSubImage2D				PROTO	:GLenum,:GLint,:GLint,:GLint,:GLsizei,:GLsizei,:GLenum,:GLenum,:ptr GLvoid
	glTranslated				PROTO	:GLdouble,:GLdouble,:GLdouble
	glTranslatef				PROTO	:GLfloat,:GLfloat,:GLfloat
	glVertex2d				PROTO	:GLdouble,:GLdouble
	glVertex2dv				PROTO	:ptr GLdouble
	glVertex2f				PROTO	:GLfloat,:GLfloat
	glVertex2fv				PROTO	:ptr GLfloat
	glVertex2i				PROTO	:GLint,:GLint
	glVertex2iv				PROTO	:ptr GLint
	glVertex2s				PROTO	:GLshort,:GLshort
	glVertex2sv				PROTO	:ptr GLshort
	glVertex3d				PROTO	:GLdouble,:GLdouble,:GLdouble
	glVertex3dv				PROTO	:ptr GLdouble
	glVertex3f				PROTO	:GLfloat,:GLfloat,:GLfloat
	glVertex3fv				PROTO	:ptr GLfloat
	glVertex3i				PROTO	:GLint,:GLint,:GLint
	glVertex3iv				PROTO	:ptr GLint
	glVertex3s				PROTO	:GLshort,:GLshort,:GLshort
	glVertex3sv				PROTO	:ptr GLshort
	glVertex4d				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble
	glVertex4dv				PROTO	:ptr GLdouble
	glVertex4f				PROTO	:GLfloat,:GLfloat,:GLfloat,:GLfloat
	glVertex4fv				PROTO	:ptr GLfloat
	glVertex4i				PROTO	:GLint,:GLint,:GLint,:GLint
	glVertex4iv				PROTO	:ptr GLint
	glVertex4s				PROTO	:GLshort,:GLshort,:GLshort,:GLshort
	glVertex4sv				PROTO	:ptr GLshort
	glVertexPointer				PROTO	:GLint,:GLenum,:GLsizei,:ptr GLvoid
	glViewport				PROTO	:GLint,:GLint,:GLsizei,:GLsizei


	gluErrorString 			PROTO   :GLenum
	gluErrorUnicodeStringEXT 	PROTO   :GLenum
	gluGetString 			PROTO   :GLenum


	gluOrtho2D				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble
	gluPerspective				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble
	gluPickMatrix				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble,:ptr GLint
	gluLookAt				PROTO	:GLdouble,:GLdouble,:GLdouble,:GLdouble,:GLdouble,:GLdouble,:GLdouble,:GLdouble,:GLdouble
	gluProject				PROTO	:GLdouble,:GLdouble,:GLdouble,:ptr GLdouble,:ptr GLdouble,:ptr GLint,:ptr GLdouble,:ptr GLdouble,:ptr GLdouble
	gluUnProject			PROTO	:GLdouble,:GLdouble,:GLdouble,:ptr GLdouble,:ptr GLdouble,:ptr GLint,:ptr GLdouble,:ptr GLdouble,:ptr GLdouble
	gluScaleImage				PROTO	:GLenum,:GLint,:GLint,:GLenum,:ptr void,:GLint,:GLint,:GLenum,:ptr
	gluBuild1DMipmaps				PROTO	:GLenum,:GLint,:GLint,:GLenum,:GLenum,:ptr
	gluBuild2DMipmaps				PROTO	:GLenum,:GLint,:GLint,:GLint,:GLenum,:GLenum,:ptr
	gluNewQuadric				PROTO	
	gluDeleteQuadric				PROTO	:ptr GLUquadric
	gluQuadricNormals				PROTO	:ptr GLUquadric,:GLenum
	gluQuadricTexture				PROTO	:ptr GLUquadric,:GLboolean
	gluQuadricOrientation				PROTO	:ptr GLUquadric,:GLenum
	gluQuadricDrawStyle				PROTO	:ptr GLUquadric,:GLenum
	gluCylinder				PROTO	:ptr GLUquadric,:GLdouble,:GLdouble,:GLdouble,:GLint,:GLint
	gluDisk				PROTO	:ptr GLUquadric,:GLdouble,:GLdouble,:GLint,:GLint
	gluPartialDisk				PROTO	:ptr GLUquadric,:GLdouble,:GLdouble,:GLint,:GLint,:GLdouble,:GLdouble
	gluSphere				PROTO	:ptr GLUquadric,:GLdouble,:GLint,:GLint
	gluQuadricCallback				PROTO	:ptr GLUquadric,:GLenum,:ptr
	gluNewTess				PROTO	
	gluDeleteTess				PROTO	:ptr GLUtesselator
	gluTessBeginPolygon				PROTO	:ptr GLUtesselator,:ptr
	gluTessBeginContour				PROTO	:ptr GLUtesselator
	gluTessVertex				PROTO	:ptr GLUtesselator,:ptr GLdouble,:ptr
	gluTessEndContour				PROTO	:ptr GLUtesselator
	gluTessEndPolygon				PROTO	:ptr GLUtesselator
	gluTessProperty				PROTO	:ptr GLUtesselator,:GLenum,:GLdouble
	gluTessNormal				PROTO	:ptr GLUtesselator,:GLdouble,:GLdouble,:GLdouble
	gluTessCallback				PROTO	:ptr GLUtesselator,:GLenum,:ptr
	gluGetTessProperty				PROTO	:ptr GLUtesselator,:GLenum,:ptr GLdouble
	gluNewNurbsRenderer				PROTO	
	gluDeleteNurbsRenderer				PROTO	:ptr GLUnurbs
	gluBeginSurface				PROTO	:ptr GLUnurbs
	gluBeginCurve				PROTO	:ptr GLUnurbs
	gluEndCurve				PROTO	:ptr GLUnurbs
	gluEndSurface				PROTO	:ptr GLUnurbs
	gluBeginTrim				PROTO	:ptr GLUnurbs
	gluEndTrim				PROTO	:ptr GLUnurbs
	gluPwlCurve				PROTO	:ptr GLUnurbs,:GLint,:ptr GLfloat,:GLint,:GLenum
	gluNurbsCurve				PROTO	:ptr GLUnurbs,:GLint,:ptr GLfloat,:GLint,:ptr GLfloat,:GLint,:GLenum
	gluNurbsSurface				PROTO	:ptr GLUnurbs,:GLint,:ptr float,:GLint,:ptr GLfloat,:GLint,:GLint,:ptr GLfloat,:GLint,:GLint,:GLenum
	gluLoadSamplingMatrices				PROTO	:ptr GLUnurbs,:ptr GLfloat,:ptr GLfloat,:ptr GLint
	gluNurbsProperty				PROTO	:ptr GLUnurbs,:GLenum,:GLfloat
	gluGetNurbsProperty				PROTO	:ptr GLUnurbs,:GLenum,:ptr GLfloat
	gluNurbsCallback				PROTO	:ptr GLUnurbs,:GLenum,:ptr
	GLU_VERSION_1_1		equ 1
	GLU_VERSION_1_2		equ 1
	GLU_INVALID_ENUM	equ 100900
	GLU_INVALID_VALUE	equ 100901
	GLU_OUT_OF_MEMORY	equ 100902
	GLU_INCOMPATIBLE_GL_VERSION equ 100903
	GLU_VERSION		equ 100800
	GLU_EXTENSIONS		equ 100801
	GLU_TRUE		equ GL_TRUE
	GLU_FALSE		equ GL_FALSE
	GLU_SMOOTH		equ 100000
	GLU_FLAT		equ 100001
	GLU_NONE		equ 100002
	GLU_POINT		equ 100010
	GLU_LINE		equ 100011
	GLU_FILL		equ 100012
	GLU_SILHOUETTE		equ 100013
	GLU_OUTSIDE		equ 100020
	GLU_INSIDE		equ 100021
	GLU_TESS_MAX_COORD	equ 1.0e150
	GLU_TESS_WINDING_RULE	equ 100140
	GLU_TESS_BOUNDARY_ONLY	equ 100141
	GLU_TESS_TOLERANCE	equ 100142
	GLU_TESS_WINDING_ODD	equ 100130
	GLU_TESS_WINDING_NONZERO equ 100131
	GLU_TESS_WINDING_POSITIVE equ 100132
	GLU_TESS_WINDING_NEGATIVE equ 100133
	GLU_TESS_WINDING_ABS_GEQ_TWO equ 100134
	GLU_TESS_BEGIN		equ 100100
	GLU_TESS_VERTEX		equ 100101
	GLU_TESS_END		equ 100102
	GLU_TESS_ERROR		equ 100103
	GLU_TESS_EDGE_FLAG	equ 100104
	GLU_TESS_COMBINE	equ 100105
	GLU_TESS_BEGIN_DATA	equ 100106
	GLU_TESS_VERTEX_DATA	equ 100107
	GLU_TESS_END_DATA	equ 100108
	GLU_TESS_ERROR_DATA	equ 100109
	GLU_TESS_EDGE_FLAG_DATA equ 100110
	GLU_TESS_COMBINE_DATA	equ 100111
	GLU_TESS_ERROR1		equ 100151
	GLU_TESS_ERROR2		equ 100152
	GLU_TESS_ERROR3		equ 100153
	GLU_TESS_ERROR4		equ 100154
	GLU_TESS_ERROR5		equ 100155
	GLU_TESS_ERROR6		equ 100156
	GLU_TESS_ERROR7		equ 100157
	GLU_TESS_ERROR8		equ 100158
	GLU_TESS_MISSING_BEGIN_POLYGON equ GLU_TESS_ERROR1
	GLU_TESS_MISSING_BEGIN_CONTOUR equ GLU_TESS_ERROR2
	GLU_TESS_MISSING_END_POLYGON equ GLU_TESS_ERROR3
	GLU_TESS_MISSING_END_CONTOUR equ GLU_TESS_ERROR4
	GLU_TESS_COORD_TOO_LARGE equ GLU_TESS_ERROR5
	GLU_TESS_NEED_COMBINE_CALLBACK equ GLU_TESS_ERROR6
	GLU_AUTO_LOAD_MATRIX	equ 100200
	GLU_CULLING		equ 100201
	GLU_SAMPLING_TOLERANCE	equ 100203
	GLU_DISPLAY_MODE	equ 100204
	GLU_PARAMETRIC_TOLERANCE equ 100202
	GLU_SAMPLING_METHOD	equ 100205
	GLU_U_STEP		equ 100206
	GLU_V_STEP		equ 100207
	GLU_PATH_LENGTH		equ 100215
	GLU_PARAMETRIC_ERROR	equ 100216
	GLU_DOMAIN_DISTANCE	equ 100217
	GLU_MAP1_TRIM_2		equ 100210
	GLU_MAP1_TRIM_3		equ 100211
	GLU_OUTLINE_POLYGON	equ 100240
	GLU_OUTLINE_PATCH	equ 100241
	GLU_NURBS_ERROR1	equ 100251
	GLU_NURBS_ERROR2	equ 100252
	GLU_NURBS_ERROR3	equ 100253
	GLU_NURBS_ERROR4	equ 100254
	GLU_NURBS_ERROR5	equ 100255
	GLU_NURBS_ERROR6	equ 100256
	GLU_NURBS_ERROR7	equ 100257
	GLU_NURBS_ERROR8	equ 100258
	GLU_NURBS_ERROR9	equ 100259
	GLU_NURBS_ERROR10	equ 100260
	GLU_NURBS_ERROR11	equ 100261
	GLU_NURBS_ERROR12	equ 100262
	GLU_NURBS_ERROR13	equ 100263
	GLU_NURBS_ERROR14	equ 100264
	GLU_NURBS_ERROR15	equ 100265
	GLU_NURBS_ERROR16	equ 100266
	GLU_NURBS_ERROR17	equ 100267
	GLU_NURBS_ERROR18	equ 100268
	GLU_NURBS_ERROR19	equ 100269
	GLU_NURBS_ERROR20	equ 100270
	GLU_NURBS_ERROR21	equ 100271
	GLU_NURBS_ERROR22	equ 100272
	GLU_NURBS_ERROR23	equ 100273
	GLU_NURBS_ERROR24	equ 100274
	GLU_NURBS_ERROR25	equ 100275
	GLU_NURBS_ERROR26	equ 100276
	GLU_NURBS_ERROR27	equ 100277
	GLU_NURBS_ERROR28	equ 100278
	GLU_NURBS_ERROR29	equ 100279
	GLU_NURBS_ERROR30	equ 100280
	GLU_NURBS_ERROR31	equ 100281
	GLU_NURBS_ERROR32	equ 100282
	GLU_NURBS_ERROR33	equ 100283
	GLU_NURBS_ERROR34	equ 100284
	GLU_NURBS_ERROR35	equ 100285
	GLU_NURBS_ERROR36	equ 100286
	GLU_NURBS_ERROR37	equ 100287
	gluBeginPolygon				PROTO	:ptr GLUtesselator
	gluNextContour				PROTO	:ptr GLUtesselator,:GLenum
	gluEndPolygon				PROTO	:ptr GLUtesselator
	GLU_CW			equ 100120
	GLU_CCW			equ 100121
	GLU_INTERIOR		equ 100122
	GLU_EXTERIOR		equ 100123
	GLU_UNKNOWN		equ 100124
	GLU_BEGIN		equ GLU_TESS_BEGIN
	GLU_VERTEX		equ GLU_TESS_VERTEX
	GLU_END			equ GLU_TESS_END
	GLU_ERROR		equ GLU_TESS_ERROR
	GLU_EDGE_FLAG		equ GLU_TESS_EDGE_FLAG
ENDIF
