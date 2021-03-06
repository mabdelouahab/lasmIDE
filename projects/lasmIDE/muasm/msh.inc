MSH STRUCT; ____MSH1
	Field_Separator		DD	0	; ST); ____MSH2
	Encoding_Characters		DD	0	; ST); ____MSH3
	Sending_Application		DD	0	; HD)_optional; ____MSH4
	Sending_Facility		         DD	0	; HD)_optional; ____MSH5
	Receiving_Application		DD	0	; HD)_optional; ____MSH6
	Receiving_Facility		DD	0	; HD)_optional; ____MSH7
	Date_Time_Of_Message		 DD	0	; TS)_optional; ____MSH8
	Security		                 DD	0	; ST)_optional; ____MSH9
	Message_Type		         DD	0	; MSG); ____MSH10
	Message_Control_ID		 DD	0	; ST); ____MSH11
	Processing_ID		         DD	0	; PT); ____MSH12
	Version_ID		         DD	0	; VID); ____MSH13
	Sequence_Number		         DD	0	; NM)_optional; ____MSH14
	Continuation_Pointer		 DD	0	; ST)_optional; ____MSH15
	Accept_Acknowledgment_Type	 DD	0	; ID)_optional; ____MSH16
	Application_Acknowledgment_Type	 DD	0	; ID)_optional; ____MSH17
	Country_Code		         DD	0	; ID)_optional; ____MSH18
	Character_Set		         DD	0	; ID)_optional_repeating; ____MSH19
	Principal_Language_Of_Message	DD	0	; CE)_optional; ____MSH20
	Alternate_Character_Set_Handling_Scheme		DD	0	; ID)_optional_
MSH ENDS
EVN STRUCT; ____EVN1
	Event_Type_Code		DD	0	; ID)_optional; ____EVN2
	Recorded_Date_Time	DD	0	; TS); ____EVN3
	Date_Time_Planned_Event	DD	0	; TS)_optional; ____EVN4
	Event_Reason_Code	DD	0	; IS)_optional; ____EVN5
	Operator_ID		DD	0	; XCN)_optional_repeating; ____EVN6
	Event_Occurred		DD	0	; TS)_optional_
EVN ENDS
PID STRUCT; ____PID1
	Set_ID__PID		DD	0	; SI)_optional; ____PID2
	Patient_ID		DD	0	; CX)_optional; ____PID3
	Patient_Identifier_List	DD	0	; CX)_repeating; ____PID4
	Alternate_Patient_ID__PID  DD	0	; CX)_optional_repeating; ____PID5
	Patient_Name		DD	0	; XPN)_repeating; ____PID6
	Mothers_Maiden_Name	DD	0	; XPN)_optional_repeating; ____PID7
	Date_Time_Of_Birth	DD	0	; TS)_optional; ____PID8
	Sex		        DD	0	; IS)_optional; ____PID9
	Patient_Alias		DD	0	; XPN)_optional_repeating; ____PID10
	Race		        DD	0	; CE)_optional_repeating; ____PID11
	Patient_Address	        DD	0	; XAD)_optional_repeating; ____PID12
	County_Code		DD	0	; IS)_optional; ____PID13
	Phone_Number__Home	DD	0	; XTN)_optional_repeating; ____PID14
	Phone_Number__Business	DD	0	; XTN)_optional_repeating; ____PID15
	Primary_Language		DD	0	; CE)_optional; ____PID16
	Marital_Status		DD	0	; CE)_optional; ____PID17
	Religion		        DD	0	; CE)_optional; ____PID18
	Patient_Account_Number	DD	0	; CX)_optional; ____PID19
	SSN_Number__Patient	DD	0	; ST)_optional; ____PID20
	Drivers_License_Number__Patient		DD	0	; DLN)_optional; ____PID21
	Mothers_Identifier	DD	0	; CX)_optional_repeating; ____PID22
	Ethnic_Group		DD	0	; CE)_optional_repeating; ____PID23
	Birth_Place		DD	0	; ST)_optional; ____PID24
	Multiple_Birth_Indicator	DD	0	; ID)_optional; ____PID25
	Birth_Order		DD	0	; NM)_optional; ____PID26
	Citizenship		DD	0	; CE)_optional_repeating; ____PID27
	Veterans_Military_Status	DD	0	; CE)_optional; ____PID28
	Nationality		DD	0	; CE)_optional; ____PID29
	Patient_Death_Date_and_Time		DD	0	; TS)_optional; ____PID30
	Patient_Death_Indicator	DD	0	; ID)_optional_
PID ENDS
NK1 STRUCT; ____NK11
	Set_ID__NK1		DD	0	; SI); ____NK12
	NK_Name		        DD	0	; XPN)_optional_repeating; ____NK13
	Relationship		DD	0	; CE)_optional; ____NK14
	Address		        DD	0	; XAD)_optional_repeating; ____NK15
	Phone_Number		DD	0	; XTN)_optional_repeating; ____NK16
	Business_Phone_Number		DD	0	; XTN)_optional_repeating; ____NK17
	Contact_Role		DD	0	; CE)_optional; ____NK18
	Start_Date		DD	0	; DT)_optional; ____NK19
	End_Date		DD	0	; DT)_optional; ____NK110
	Next_of_Kin__Associated_Parties_Job_Title		DD	0	; ST)_optional; ____NK111
	Next_of_Kin__Associated_Parties_Job_CodeClass		DD	0	; JCC)_optional; ____NK112
	Next_of_Kin__Associated_Parties_Employee_Number		DD	0	; CX)_optional; ____NK113
	Organization_Name__NK1		DD	0	; XON)_optional_repeating; ____NK114
	Marital_Status		DD	0	; CE)_optional; ____NK115
	Sex		DD	0	; IS)_optional; ____NK116
	Date_Time_Of_Birth		DD	0	; TS)_optional; ____NK117
	Living_Dependency		DD	0	; IS)_optional_repeating; ____NK118
	Ambulatory_Status		DD	0	; IS)_optional_repeating; ____NK119
	Citizenship		DD	0	; CE)_optional_repeating; ____NK120
	Primary_Language		DD	0	; CE)_optional; ____NK121
	Living_Arrangement		DD	0	; IS)_optional; ____NK122
	Publicity_Code		DD	0	; CE)_optional; ____NK123
	Protection_Indicator		DD	0	; ID)_optional; ____NK124
	Student_Indicator		DD	0	; IS)_optional; ____NK125
	Religion		DD	0	; CE)_optional; ____NK126
	Mothers_Maiden_Name		DD	0	; XPN)_optional_repeating; ____NK127
	Nationality		DD	0	; CE)_optional; ____NK128
	Ethnic_Group		DD	0	; CE)_optional_repeating; ____NK129
	Contact_Reason		DD	0	; CE)_optional_repeating; ____NK130
	Contact_Persons_Name		DD	0	; XPN)_optional_repeating; ____NK131
	Contact_Persons_Telephone_Number		DD	0	; XTN)_optional_repeating; ____NK132
	Contact_Persons_Address		DD	0	; XAD)_optional_repeating; ____NK133
	Next_of_KinAssociated_Partys_Identifiers		DD	0	; CX)_optional_repeating; ____NK134
	Job_Status		DD	0	; IS)_optional; ____NK135
	Race		DD	0	; CE)_optional_repeating; ____NK136
	Handicap		DD	0	; IS)_optional; ____NK137
	Contact_Person_Social_Security_Number		DD	0	; ST)_optional_
NK1 ENDS
PV1 STRUCT; ____PV11
	Set_ID__PV1		DD	0	; SI)_optional; ____PV12
	Patient_Class		DD	0	; IS); ____PV13
	Assigned_Patient_Location		DD	0	; PL)_optional; ____PV14
	Admission_Type		DD	0	; IS)_optional; ____PV15
	Preadmit_Number		DD	0	; CX)_optional; ____PV16
	Prior_Patient_Location		DD	0	; PL)_optional; ____PV17
	Attending_Doctor		DD	0	; XCN)_optional_repeating; ____PV18
	Referring_Doctor		DD	0	; XCN)_optional_repeating; ____PV19
	Consulting_Doctor		DD	0	; XCN)_optional_repeating; ____PV110
	Hospital_Service		DD	0	; IS)_optional; ____PV111
	Temporary_Location		DD	0	; PL)_optional; ____PV112
	Preadmit_Test_Indicator		DD	0	; IS)_optional; ____PV113
	Readmission_Indicator		DD	0	; IS)_optional; ____PV114
	Admit_Source		DD	0	; IS)_optional; ____PV115
	Ambulatory_Status		DD	0	; IS)_optional_repeating; ____PV116
	VIP_Indicator		DD	0	; IS)_optional; ____PV117
	Admitting_Doctor		DD	0	; XCN)_optional_repeating; ____PV118
	Patient_Type		DD	0	; IS)_optional; ____PV119
	Visit_Number		DD	0	; CX)_optional; ____PV120
	Financial_Class		DD	0	; FC)_optional_repeating; ____PV121
	Charge_Price_Indicator		DD	0	; IS)_optional; ____PV122
	Courtesy_Code		DD	0	; IS)_optional; ____PV123
	Credit_Rating		DD	0	; IS)_optional; ____PV124
	Contract_Code		DD	0	; IS)_optional_repeating; ____PV125
	Contract_Effective_Date		DD	0	; DT)_optional_repeating; ____PV126
	Contract_Amount		DD	0	; NM)_optional_repeating; ____PV127
	Contract_Period		DD	0	; NM)_optional_repeating; ____PV128
	Interest_Code		DD	0	; IS)_optional; ____PV129
	Transfer_to_Bad_Debt_Code		DD	0	; IS)_optional; ____PV130
	Transfer_to_Bad_Debt_Date		DD	0	; DT)_optional; ____PV131
	Bad_Debt_Agency_Code		DD	0	; IS)_optional; ____PV132
	Bad_Debt_Transfer_Amount		DD	0	; NM)_optional; ____PV133
	Bad_Debt_Recovery_Amount		DD	0	; NM)_optional; ____PV134
	Delete_Account_Indicator		DD	0	; IS)_optional; ____PV135
	Delete_Account_Date		DD	0	; DT)_optional; ____PV136
	Discharge_Disposition		DD	0	; IS)_optional; ____PV137
	Discharged_to_Location		DD	0	; DLD)_optional; ____PV138
	Diet_Type		DD	0	; CE)_optional; ____PV139
	Servicing_Facility		DD	0	; IS)_optional; ____PV140
	Bed_Status		DD	0	; IS)_optional; ____PV141
	Account_Status		DD	0	; IS)_optional; ____PV142
	Pending_Location		DD	0	; PL)_optional; ____PV143
	Prior_Temporary_Location		DD	0	; PL)_optional; ____PV144
	Admit_Date_Time		DD	0	; TS)_optional; ____PV145
	Discharge_Date_Time		DD	0	; TS)_optional; ____PV146
	Current_Patient_Balance		DD	0	; NM)_optional; ____PV147
	Total_Charges		DD	0	; NM)_optional; ____PV148
	Total_Adjustments		DD	0	; NM)_optional; ____PV149
	Total_Payments		DD	0	; NM)_optional; ____PV150
	Alternate_Visit_ID		DD	0	; CX)_optional; ____PV151
	Visit_Indicator		DD	0	; IS)_optional; ____PV152
	Other_Healthcare_Provider		DD	0	; XCN)_optional_repeating_
PV1 ENDS
OBR STRUCT; ____OBR1
	Set_ID__OBR		DD	0	; SI)_optional; ____OBR2
	Placer_Order_Number		DD	0	; EI)_optional; ____OBR3
	Filler_Order_Number		DD	0	; EI)_optional; ____OBR4
	Universal_Service_ID		DD	0	; CE); ____OBR5
	PriorityOBR		DD	0	; ID)_optional; ____OBR6
	Requested_Date_Time		DD	0	; TS)_optional; ____OBR7
	Observation_Date_Time_		DD	0	; TS)_optional; ____OBR8
	Observation_End_Date_Time_		DD	0	; TS)_optional; ____OBR9
	Collection_Volume_		DD	0	; CQ)_optional; ____OBR10
	Collector_Identifier_		DD	0	; XCN)_optional_repeating; ____OBR11
	Specimen_Action_Code_		DD	0	; ID)_optional; ____OBR12
	Danger_Code		DD	0	; CE)_optional; ____OBR13
	Relevant_Clinical_Info		DD	0	; ST)_optional; ____OBR14
	Specimen_Received_Date_Time_		DD	0	; TS)_optional; ____OBR15
	Specimen_Source		DD	0	; SPS)_optional; ____OBR16
	Ordering_Provider		DD	0	; XCN)_optional_repeating; ____OBR17
	Order_Callback_Phone_Number		DD	0	; XTN)_optional_repeating; ____OBR18
	Placer_Field_1		DD	0	; ST)_optional; ____OBR19
	Placer_Field_2		DD	0	; ST)_optional; ____OBR20
	Filler_Field_1_		DD	0	; ST)_optional; ____OBR21
	Filler_Field_2_		DD	0	; ST)_optional; ____OBR22
	Results_RptStatus_Chng__Date_Time_		DD	0	; TS)_optional; ____OBR23
	Charge_to_Practice_		DD	0	; MOC)_optional; ____OBR24
	Diagnostic_Serv_Sect_ID		DD	0	; ID)_optional; ____OBR25
	Result_Status_		DD	0	; ID)_optional; ____OBR26
	Parent_Result_		DD	0	; PRL)_optional; ____OBR27
	QuantityTiming		DD	0	; TQ)_optional_repeating; ____OBR28
	Result_Copies_To		DD	0	; XCN)_optional_repeating; ____OBR29
	Parent_Number		DD	0	; EIP)_optional; ____OBR30
	Transportation_Mode		DD	0	; ID)_optional; ____OBR31
	Reason_for_Study		DD	0	; CE)_optional_repeating; ____OBR32
	Principal_Result_Interpreter_		DD	0	; NDL)_optional; ____OBR33
	Assistant_Result_Interpreter_		DD	0	; NDL)_optional_repeating; ____OBR34
	Technician_		DD	0	; NDL)_optional_repeating; ____OBR35
	Transcriptionist_		DD	0	; NDL)_optional_repeating; ____OBR36
	Scheduled_Date_Time_		DD	0	; TS)_optional; ____OBR37
	Number_of_Sample_Containers_		DD	0	; NM)_optional; ____OBR38
	Transport_Logistics_of_Collected_Sample_		DD	0	; CE)_optional_repeating; ____OBR39
	Collectors_Comment_		DD	0	; CE)_optional_repeating; ____OBR40
	Transport_Arrangement_Responsibility		DD	0	; CE)_optional; ____OBR41
	Transport_Arranged		DD	0	; ID)_optional; ____OBR42
	Escort_Required		DD	0	; ID)_optional; ____OBR43
	Planned_Patient_Transport_Comment		DD	0	; CE)_optional_repeating; ____OBR44
	Procedure_Code		DD	0	; CE)_optional; ____OBR45
	Procedure_Code_Modifier		DD	0	; CE)_optional_repeating_
OBR ENDS
OBX STRUCT; ____OBX1
	Set_ID__OBX		DD	0	; SI)_optional; ____OBX2
	Value_Type		DD	0	; ID); ____OBX3
	Observation_Identifier		DD	0	; CE); ____OBX4
	Observation_SubID		DD	0	; ST); ____OBX5
	Observation_Value		DD	0	; Varies)_optional_repeating; ____OBX6
	Units		DD	0	; CE)_optional; ____OBX7
	References_Range		DD	0	; ST)_optional; ____OBX8
	Abnormal_Flags		DD	0	; ID)_optional_repeating; ____OBX9
	Probability		DD	0	; NM)_optional_repeating; ____OBX10
	Nature_of_Abnormal_Test		DD	0	; ID)_optional; ____OBX11
	Observation_Result_Status		DD	0	; ID); ____OBX12
	Date_Last_Obs_Normal_Values		DD	0	; TS)_optional; ____OBX13
	User_Defined_Access_Checks		DD	0	; ST)_optional; ____OBX14
	Date_Time_of_the_Observation		DD	0	; TS)_optional; ____OBX15
	Producers_ID		DD	0	; CE)_optional; ____OBX16
	Responsible_Observer		DD	0	; XCN)_optional_repeating; ____OBX17
	Observation_Method		DD	0	; CE)_optional_repeating_
OBX ENDS
ORC STRUCT; ____ORC1
	Order_Control		DD	0	; ID)_optional; ____ORC2
	Placer_Order_Number		DD	0	; EI)_optional; ____ORC3
	Filler_Order_Number		DD	0	; EI)_optional; ____ORC4
	Placer_Group_Number		DD	0	; EI)_optional; ____ORC5
	Order_Status		DD	0	; ID)_optional; ____ORC6
	Response_Flag		DD	0	; ID)_optional; ____ORC7
	QuantityTiming		DD	0	; TQ)_optional; ____ORC8
	Parent_Order		DD	0	; EIP)_optional; ____ORC9
	Date_Time_of_Transaction		DD	0	; TS)_optional; ____ORC10
	Entered_By		DD	0	; XCN)_optional_repeating; ____ORC11
	Verified_By		DD	0	; XCN)_optional_repeating; ____ORC12
	Ordering_Provider		DD	0	; XCN)_optional_repeating; ____ORC13
	Enterers_Location		DD	0	; PL)_optional; ____ORC14
	Call_Back_Phone_Number		DD	0	; XTN)_optional_repeating; ____ORC15
	Order_Effective_Date_Time		DD	0	; TS)_optional; ____ORC16
	Order_Control_Code_Reason		DD	0	; CE)_optional; ____ORC17
	Entering_Organization		DD	0	; CE)_optional; ____ORC18
	Entering_Device		DD	0	; CE)_optional; ____ORC19
	Action_By		DD	0	; XCN)_optional_repeating; ____ORC20
	Advanced_Beneficiary_Notice_Code		DD	0	; CE)_optional; ____ORC21
	Ordering_Facility_Name		DD	0	; XON)_optional_repeating; ____ORC22
	Ordering_Facility_Address		DD	0	; XAD)_optional_repeating; ____ORC23
	Ordering_Facility_Phone_Number		DD	0	; XTN)_optional_repeating; ____ORC24
	Ordering_Provider_Address		DD	0	; XAD)_optional_repeating_
ORC ENDS
NTE STRUCT; ____NTE1
	Set_ID__NTE		DD	0	; SI)_optional; ____NTE2
	Source_of_Comment		DD	0	; ID)_optional; ____NTE3
	Comment		DD	0	; FT)_optional_repeating; ____NTE4
	Comment_Type		DD	0	; CE)_optional_
NTE ENDS
IN1 STRUCT; ____IN11
	Set_ID__IN1		DD	0	; SI); ____IN12
	Insurance_Plan_ID		DD	0	; CE); ____IN13
	Insurance_Company_ID		DD	0	; CX)_repeating; ____IN14
	Insurance_Company_Name		DD	0	; XON)_optional_repeating; ____IN15
	Insurance_Company_Address		DD	0	; XAD)_optional_repeating; ____IN16
	Insurance_Co_Contact_Person		DD	0	; XPN)_optional_repeating; ____IN17
	Insurance_Co_Phone_Number		DD	0	; XTN)_optional_repeating; ____IN18
	Group_Number		DD	0	; ST)_optional; ____IN19
	Group_Name		DD	0	; XON)_optional_repeating; ____IN110
	Insureds_Group_Emp_ID		DD	0	; CX)_optional_repeating; ____IN111
	Insureds_Group_Emp_Name		DD	0	; XON)_optional_repeating; ____IN112
	Plan_Effective_Date		DD	0	; DT)_optional; ____IN113
	Plan_Expiration_Date		DD	0	; DT)_optional; ____IN114
	Authorization_Information		DD	0	; AUI)_optional; ____IN115
	Plan_Type		DD	0	; IS)_optional; ____IN116
	Name_Of_Insured		DD	0	; XPN)_optional_repeating; ____IN117
	Insureds_Relationship_To_Patient		DD	0	; CE)_optional; ____IN118
	Insureds_Date_Of_Birth		DD	0	; TS)_optional; ____IN119
	Insureds_Address		DD	0	; XAD)_optional_repeating; ____IN120
	Assignment_Of_Benefits		DD	0	; IS)_optional; ____IN121
	Coordination_Of_Benefits		DD	0	; IS)_optional; ____IN122
	Coord_Of_Ben_Priority		DD	0	; ST)_optional; ____IN123
	Notice_Of_Admission_Flag		DD	0	; ID)_optional; ____IN124
	Notice_Of_Admission_Date		DD	0	; DT)_optional; ____IN125
	Report_Of_Eligibility_Flag		DD	0	; ID)_optional; ____IN126
	Report_Of_Eligibility_Date		DD	0	; DT)_optional; ____IN127
	Release_Information_Code		DD	0	; IS)_optional; ____IN128
	PreAdmit_Cert		DD	0	; PAC)		DD	0	; ST)_optional; ____IN129
	Verification_Date_Time		DD	0	; TS)_optional; ____IN130
	Verification_By		DD	0	; XCN)_optional_repeating; ____IN131
	Type_Of_Agreement_Code		DD	0	; IS)_optional; ____IN132
	Billing_Status		DD	0	; IS)_optional; ____IN133
	Lifetime_Reserve_Days		DD	0	; NM)_optional; ____IN134
	Delay_Before_LR_Day		DD	0	; NM)_optional; ____IN135
	Company_Plan_Code		DD	0	; IS)_optional; ____IN136
	Policy_Number		DD	0	; ST)_optional; ____IN137
	Policy_Deductible		DD	0	; CP)_optional; ____IN138
	Policy_Limit__Amount		DD	0	; CP)_optional; ____IN139
	Policy_Limit__Days		DD	0	; NM)_optional; ____IN140
	Room_Rate__SemiPrivate		DD	0	; CP)_optional; ____IN141
	Room_Rate__Private		DD	0	; CP)_optional; ____IN142
	Insureds_Employment_Status		DD	0	; CE)_optional; ____IN143
	Insureds_Sex		DD	0	; IS)_optional; ____IN144
	Insureds_Employers_Address		DD	0	; XAD)_optional_repeating; ____IN145
	Verification_Status		DD	0	; ST)_optional; ____IN146
	Prior_Insurance_Plan_ID		DD	0	; IS)_optional; ____IN147
	Coverage_Type		DD	0	; IS)_optional; ____IN148
	Handicap		DD	0	; IS)_optional; ____IN149
	Insureds_ID_Number		DD	0	; CX)_optional_repeating_
IN1 ENDS
GT1 STRUCT; ____GT11
	Set_ID__GT1		DD	0	; SI); ____GT12
	Guarantor_Number		DD	0	; CX)_optional_repeating; ____GT13
	Guarantor_Name		DD	0	; XPN)_repeating; ____GT14
	Guarantor_Spouse_Name		DD	0	; XPN)_optional_repeating; ____GT15
	Guarantor_Address		DD	0	; XAD)_optional_repeating; ____GT16
	Guarantor_Ph_NumHome		DD	0	; XTN)_optional_repeating; ____GT17
	Guarantor_Ph_NumBusiness		DD	0	; XTN)_optional_repeating; ____GT18
	Guarantor_Date_Time_Of_Birth		DD	0	; TS)_optional; ____GT19
	Guarantor_Sex		DD	0	; IS)_optional; ____GT110
	Guarantor_Type		DD	0	; IS)_optional; ____GT111
	Guarantor_Relationship		DD	0	; CE)_optional; ____GT112
	Guarantor_SSN		DD	0	; ST)_optional; ____GT113
	Guarantor_Date__Begin		DD	0	; DT)_optional; ____GT114
	Guarantor_Date__End		DD	0	; DT)_optional; ____GT115
	Guarantor_Priority		DD	0	; NM)_optional; ____GT116
	Guarantor_Employer_Name		DD	0	; XPN)_optional_repeating; ____GT117
	Guarantor_Employer_Address		DD	0	; XAD)_optional_repeating; ____GT118
	Guarantor_Employer_Phone_Number		DD	0	; XTN)_optional_repeating; ____GT119
	Guarantor_Employee_ID_Number		DD	0	; CX)_optional_repeating; ____GT120
	Guarantor_Employment_Status		DD	0	; IS)_optional; ____GT121
	Guarantor_Organization_Name		DD	0	; XON)_optional_repeating; ____GT122
	Guarantor_Billing_Hold_Flag		DD	0	; ID)_optional; ____GT123
	Guarantor_Credit_Rating_Code		DD	0	; CE)_optional; ____GT124
	Guarantor_Death_Date_And_Time		DD	0	; TS)_optional; ____GT125
	Guarantor_Death_Flag		DD	0	; ID)_optional; ____GT126
	Guarantor_Charge_Adjustment_Code		DD	0	; CE)_optional; ____GT127
	Guarantor_Household_Annual_Income		DD	0	; CP)_optional; ____GT128
	Guarantor_Household_Size		DD	0	; NM)_optional; ____GT129
	Guarantor_Employer_ID_Number		DD	0	; CX)_optional_repeating; ____GT130
	Guarantor_Marital_Status_Code		DD	0	; CE)_optional; ____GT131
	Guarantor_Hire_Effective_Date		DD	0	; DT)_optional; ____GT132
	Employment_Stop_Date		DD	0	; DT)_optional; ____GT133
	Living_Dependency		DD	0	; IS)_optional; ____GT134
	Ambulatory_Status		DD	0	; IS)_optional_repeating; ____GT135
	Citizenship		DD	0	; CE)_optional_repeating; ____GT136
	Primary_Language		DD	0	; CE)_optional; ____GT137
	Living_Arrangement		DD	0	; IS)_optional; ____GT138
	Publicity_Code		DD	0	; CE)_optional; ____GT139
	Protection_Indicator		DD	0	; ID)_optional; ____GT140
	Student_Indicator		DD	0	; IS)_optional; ____GT141
	Religion		DD	0	; CE)_optional; ____GT142
	Mothers_Maiden_Name		DD	0	; XPN)_optional_repeating; ____GT143
	Nationality		DD	0	; CE)_optional; ____GT144
	Ethnic_Group		DD	0	; CE)_optional_repeating; ____GT145
	Contact_Persons_Name		DD	0	; XPN)_optional_repeating; ____GT146
	Contact_Persons_Telephone_Number		DD	0	; XTN)_optional_repeating; ____GT147
	Contact_Reason		DD	0	; CE)_optional; ____GT148
	Contact_Relationship		DD	0	; IS)_optional; ____GT149
	Job_Title		DD	0	; ST)_optional; ____GT150
	Job_CodeClass		DD	0	; JCC)_optional; ____GT151
	Guarantor_Employers_Organization_Name		DD	0	; XON)_optional_repeating; ____GT152
	Handicap		DD	0	; IS)_optional; ____GT153
	Job_Status		DD	0	; IS)_optional; ____GT154
	Guarantor_Financial_Class		DD	0	; FC)_optional; ____GT155
	Guarantor_Race		DD	0	; CE)_optional_repeating_
GT1 ENDS

