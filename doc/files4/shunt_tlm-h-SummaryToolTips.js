﻿NDSummary.OnToolTipsLoaded("File4:shunt_tlm.h",{8:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_tlm_print_csgp(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">cs_tlm_generic_payload_header&nbsp;</td><td class=\"PName\">csgp,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">string</span>&nbsp;</td><td class=\"PName\">prefix</td><td class=\"PDefaultValueSeparator\">&nbsp;=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHString\">&quot;&quot;</span></td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">print Client-Server Generic Payload (csgp header) structure</div></div>",9:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_tlm_print_axi3_header(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">cs_tlm_axi3_extension_payload_header&nbsp;</td><td class=\"PName\">h_axi3,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">string</span>&nbsp;</td><td class=\"PName\">prefix</td><td class=\"PDefaultValueSeparator\">&nbsp;=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHString\">&quot;&quot;</span></td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">print shunt axi3 header structure(cs_tlm_axi3_extension_payload_header)</div></div>",10:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype10\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">int</span> is_shunt_tlm_end_sim(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">cs_tlm_generic_payload_header&nbsp;</td><td class=\"PName last\">csgp</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">get simulation status</div></div>",11:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype11\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_tlmgp2csgp(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\">cs_tlm_generic_payload_header&nbsp;</td><td class=\"PSymbols\">*</td><td class=\"PName last\">csgp,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> tlm::</td><td class=\"PType\">tlm_generic_payload&amp;&nbsp;</td><td></td><td class=\"PName last\">tlmgp</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">map tlm Generic Payload (tlmgp) object to Client-Server Generic Payload (csgp header) structure.</div></div>",12:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype12\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_csgp2tlmgp (</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">tlm::</td><td class=\"PType\">tlm_generic_payload&amp;&nbsp;</td><td></td><td class=\"PName last\">tlmgp,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">cs_tlm_generic_payload_header&nbsp;</td><td class=\"PSymbols\">*</td><td class=\"PName last\">csgp</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">map Client-Server Generic Payload (csgp header) structure to tlm Generic Payload (tlmgp) object</div></div>",13:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype13\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\">tlm_phase_enum shunt_tlm_get_phase_enum(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">tlm_phase&amp;&nbsp;</td><td class=\"PName last\">phase</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">map tlm_phase object to tlm_phase_enum</div></div>",16:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype16\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">int</span> shunt_tlm_init_server(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName\">port</td><td class=\"PDefaultValueSeparator\">&nbsp;=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHNumber\">0</span></td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">TCP/IP Server initialization</div></div>",17:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype17\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">int</span> shunt_tlm_init_client(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName last\">port,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\"><span class=\"SHKeyword\">char</span>*&nbsp;</td><td class=\"PName last\">host</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">TCP/IP Client initialization</div></div>",20:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype20\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_tlm_send_transport(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName last\">socket,</td></tr><tr><td class=\"PModifierQualifier first\">tlm::</td><td class=\"PType\">tlm_generic_payload&amp;&nbsp;</td><td class=\"PName last\">trans,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">cs_tlm_generic_payload_header&amp;&nbsp;</td><td class=\"PName last\">csgp,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">sc_time&amp;&nbsp;</td><td class=\"PName last\">delay,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">tlm_phase_enum &amp;&nbsp;</td><td class=\"PName last\">phase</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">send tlm generic payload&nbsp; packet ( cs_tlm_generic_payload_header&nbsp; + byte data vector + byte_enable vector )</div></div>",21:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype21\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_tlm_recv_transport(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName last\">socket,</td></tr><tr><td class=\"PModifierQualifier first\">tlm::</td><td class=\"PType\">tlm_generic_payload&amp;&nbsp;</td><td class=\"PName last\">trans,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">cs_tlm_generic_payload_header&amp;&nbsp;</td><td class=\"PName last\">csgp</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">receive tlm generic payload&nbsp; packet ( cs_tlm_generic_payload_header&nbsp; + byte data vector + byte_enable vector )</div></div>",22:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype22\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_tlm_send_command(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName last\">socket,</td></tr><tr><td class=\"PType first\">shunt_tlm_command&nbsp;</td><td class=\"PName last\">Com</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">send hunt_tlm_command</div></div>",23:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype23\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_tlm_recv_command(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName last\">socket,</td></tr><tr><td class=\"PType first\">shunt_tlm_command*&nbsp;</td><td class=\"PName last\">Com</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">recv hunt_tlm_command</div></div>",26:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype26\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_send_b_transport(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName last\">socket,</td></tr><tr><td class=\"PModifierQualifier first\">tlm::</td><td class=\"PType\">tlm_generic_payload&amp;&nbsp;</td><td class=\"PName last\">trans,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">shunt_long_t&nbsp;</td><td class=\"PName last\">tlm_extension_id,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">sc_time&amp;&nbsp;</td><td class=\"PName last\">delay</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">TLM b_transport analogy&nbsp; (source side).</div></div>",27:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype27\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_recv_b_transport(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName\">socket,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">tlm::</td><td class=\"PType\">tlm_generic_payload&amp;&nbsp;</td><td class=\"PName\">trans,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\">shunt_long_t&amp;&nbsp;</td><td class=\"PName\">tlm_extension_id,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\">sc_time&amp;&nbsp;</td><td class=\"PName\">delay,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\">sc_time_unit&nbsp;</td><td class=\"PName\">sc_time_units</td><td class=\"PDefaultValueSeparator\">&nbsp;=&nbsp;</td><td class=\"PDefaultValue last\">SC_NS</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">TLM b_transport analogy&nbsp; (receiver side)</div></div>",30:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype30\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_send_nb_transport(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td></td><td class=\"PName last\">socket,</td></tr><tr><td class=\"PModifierQualifier first\">tlm::</td><td class=\"PType\">tlm_generic_payload&amp;&nbsp;</td><td></td><td class=\"PName last\">trans,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">shunt_long_t&nbsp;</td><td></td><td class=\"PName last\">tlm_extension_id,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">tlm_phase&nbsp;</td><td class=\"PSymbols\">&amp;</td><td class=\"PName last\">phase,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">sc_time&amp;&nbsp;</td><td></td><td class=\"PName last\">delay</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">TLM nb_transport_fw/nb_transport_bw analogy&nbsp; (source side).</div></div>",31:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype31\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\">tlm_sync_enum shunt_recv_nb_transport_tlm_sync_resp(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName last\">socket,</td></tr><tr><td class=\"PType first\">shunt_long_t&amp;&nbsp;</td><td class=\"PName last\">tlm_extension_id</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">complementary function for shunt_send_nb_transport (source side)</div></div>",32:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype32\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_recv_nb_transport(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td></td><td class=\"PName\">socket,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">tlm::</td><td class=\"PType\">tlm_generic_payload&amp;&nbsp;</td><td></td><td class=\"PName\">trans,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\">shunt_long_t&amp;&nbsp;</td><td></td><td class=\"PName\">tlm_extension_id,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\">tlm_phase&nbsp;</td><td class=\"PSymbols\">&amp;</td><td class=\"PName\">phase,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\">sc_time&amp;&nbsp;</td><td></td><td class=\"PName\">delay,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\">sc_time_unit&nbsp;</td><td></td><td class=\"PName\">sc_time_units</td><td class=\"PDefaultValueSeparator\">&nbsp;=&nbsp;</td><td class=\"PDefaultValue last\">SC_PS</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">TLM nb_transport_fw/nb_transport_bw analogy (receiver side)</div></div>",33:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype33\" class=\"NDPrototype WideForm\"><div class=\"PSection PParameterSection CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> shunt_send_nb_transport_tlm_sync_resp(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName last\">socket,</td></tr><tr><td class=\"PType first\">tlm_sync_enum&nbsp;</td><td class=\"PName last\">tlm_sync,</td></tr><tr><td class=\"PType first\">shunt_long_t&nbsp;</td><td class=\"PName last\">tlm_extension_id</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div><div class=\"TTSummary\">complementary function for&nbsp; shunt_recv_nb_transport (receiver side)</div></div>"});