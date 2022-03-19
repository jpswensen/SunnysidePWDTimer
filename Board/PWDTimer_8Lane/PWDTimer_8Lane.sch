<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="ESP32-DEVKITC-32D">
<packages>
<package name="MODULE_ESP32-DEVKITC-32D">
<wire x1="-13.95" y1="27.15" x2="13.95" y2="27.15" width="0.127" layer="51"/>
<wire x1="13.95" y1="27.15" x2="13.95" y2="-27.25" width="0.127" layer="51"/>
<wire x1="13.95" y1="-27.25" x2="-13.95" y2="-27.25" width="0.127" layer="51"/>
<wire x1="-13.95" y1="-27.25" x2="-13.95" y2="27.15" width="0.127" layer="51"/>
<wire x1="-13.95" y1="-27.25" x2="-13.95" y2="27.15" width="0.127" layer="21"/>
<wire x1="-13.95" y1="27.15" x2="13.95" y2="27.15" width="0.127" layer="21"/>
<wire x1="13.95" y1="27.15" x2="13.95" y2="-27.25" width="0.127" layer="21"/>
<wire x1="13.95" y1="-27.25" x2="-13.95" y2="-27.25" width="0.127" layer="21"/>
<wire x1="-14.2" y1="27.4" x2="14.2" y2="27.4" width="0.05" layer="39"/>
<wire x1="14.2" y1="27.4" x2="14.2" y2="-27.5" width="0.05" layer="39"/>
<wire x1="14.2" y1="-27.5" x2="-14.2" y2="-27.5" width="0.05" layer="39"/>
<wire x1="-14.2" y1="-27.5" x2="-14.2" y2="27.4" width="0.05" layer="39"/>
<text x="-14.0054" y="27.8108" size="1.270490625" layer="25">&gt;NAME</text>
<text x="-14.0146" y="-28.9302" size="1.27133125" layer="27">&gt;VALUE</text>
<circle x="-14.6" y="19.9" radius="0.14" width="0.28" layer="27"/>
<circle x="-14.6" y="19.9" radius="0.14" width="0.28" layer="51"/>
<pad name="1" x="-12.7" y="19.76" drill="1.04" shape="square"/>
<pad name="2" x="-12.7" y="17.22" drill="1.04"/>
<pad name="19" x="-12.7" y="-25.96" drill="1.04"/>
<pad name="3" x="-12.7" y="14.68" drill="1.04"/>
<pad name="4" x="-12.7" y="12.14" drill="1.04"/>
<pad name="5" x="-12.7" y="9.6" drill="1.04"/>
<pad name="6" x="-12.7" y="7.06" drill="1.04"/>
<pad name="7" x="-12.7" y="4.52" drill="1.04"/>
<pad name="8" x="-12.7" y="1.98" drill="1.04"/>
<pad name="9" x="-12.7" y="-0.56" drill="1.04"/>
<pad name="10" x="-12.7" y="-3.1" drill="1.04"/>
<pad name="11" x="-12.7" y="-5.64" drill="1.04"/>
<pad name="12" x="-12.7" y="-8.18" drill="1.04"/>
<pad name="13" x="-12.7" y="-10.72" drill="1.04"/>
<pad name="14" x="-12.7" y="-13.26" drill="1.04"/>
<pad name="15" x="-12.7" y="-15.8" drill="1.04"/>
<pad name="16" x="-12.7" y="-18.34" drill="1.04"/>
<pad name="17" x="-12.7" y="-20.88" drill="1.04"/>
<pad name="18" x="-12.7" y="-23.42" drill="1.04"/>
<pad name="20" x="12.7" y="19.76" drill="1.04"/>
<pad name="21" x="12.7" y="17.22" drill="1.04"/>
<pad name="22" x="12.7" y="14.68" drill="1.04"/>
<pad name="23" x="12.7" y="12.14" drill="1.04"/>
<pad name="24" x="12.7" y="9.6" drill="1.04"/>
<pad name="25" x="12.7" y="7.06" drill="1.04"/>
<pad name="26" x="12.7" y="4.52" drill="1.04"/>
<pad name="27" x="12.7" y="1.98" drill="1.04"/>
<pad name="28" x="12.7" y="-0.56" drill="1.04"/>
<pad name="29" x="12.7" y="-3.1" drill="1.04"/>
<pad name="30" x="12.7" y="-5.64" drill="1.04"/>
<pad name="31" x="12.7" y="-8.18" drill="1.04"/>
<pad name="32" x="12.7" y="-10.72" drill="1.04"/>
<pad name="33" x="12.7" y="-13.26" drill="1.04"/>
<pad name="34" x="12.7" y="-15.8" drill="1.04"/>
<pad name="35" x="12.7" y="-18.34" drill="1.04"/>
<pad name="36" x="12.7" y="-20.88" drill="1.04"/>
<pad name="37" x="12.7" y="-23.42" drill="1.04"/>
<pad name="38" x="12.7" y="-25.96" drill="1.04"/>
</package>
</packages>
<symbols>
<symbol name="ESP32-DEVKITC-32D">
<wire x1="-15.24" y1="25.4" x2="15.24" y2="25.4" width="0.254" layer="94"/>
<wire x1="15.24" y1="25.4" x2="15.24" y2="-25.4" width="0.254" layer="94"/>
<wire x1="15.24" y1="-25.4" x2="-15.24" y2="-25.4" width="0.254" layer="94"/>
<wire x1="-15.24" y1="-25.4" x2="-15.24" y2="25.4" width="0.254" layer="94"/>
<text x="-15.2572" y="26.0643" size="1.78" layer="95">&gt;NAME</text>
<text x="-15.2563" y="-27.9698" size="1.7799" layer="96">&gt;VALUE</text>
<pin name="3V3" x="-20.32" y="22.86" length="middle" direction="pwr"/>
<pin name="EN" x="-20.32" y="20.32" length="middle" direction="in"/>
<pin name="SENSOR_VP" x="-20.32" y="17.78" length="middle" direction="in"/>
<pin name="SENSOR_VN" x="-20.32" y="15.24" length="middle" direction="in"/>
<pin name="IO34" x="-20.32" y="12.7" length="middle"/>
<pin name="IO35" x="-20.32" y="10.16" length="middle"/>
<pin name="IO32" x="-20.32" y="7.62" length="middle"/>
<pin name="IO33" x="-20.32" y="5.08" length="middle"/>
<pin name="IO25" x="-20.32" y="2.54" length="middle"/>
<pin name="IO26" x="-20.32" y="0" length="middle"/>
<pin name="IO27" x="-20.32" y="-2.54" length="middle"/>
<pin name="IO14" x="-20.32" y="-5.08" length="middle"/>
<pin name="IO12" x="-20.32" y="-7.62" length="middle"/>
<pin name="GND1" x="-20.32" y="-10.16" length="middle" direction="pwr"/>
<pin name="IO13" x="-20.32" y="-12.7" length="middle"/>
<pin name="SD2" x="-20.32" y="-15.24" length="middle"/>
<pin name="SD3" x="-20.32" y="-17.78" length="middle"/>
<pin name="CMD" x="-20.32" y="-20.32" length="middle"/>
<pin name="EXT_5V" x="-20.32" y="-22.86" length="middle" direction="pwr"/>
<pin name="CLK" x="20.32" y="-22.86" length="middle" direction="in" function="clk" rot="R180"/>
<pin name="SD0" x="20.32" y="-20.32" length="middle" rot="R180"/>
<pin name="SD1" x="20.32" y="-17.78" length="middle" rot="R180"/>
<pin name="IO15" x="20.32" y="-15.24" length="middle" rot="R180"/>
<pin name="IO2" x="20.32" y="-12.7" length="middle" rot="R180"/>
<pin name="IO0" x="20.32" y="-10.16" length="middle" rot="R180"/>
<pin name="IO4" x="20.32" y="-7.62" length="middle" rot="R180"/>
<pin name="IO16" x="20.32" y="-5.08" length="middle" rot="R180"/>
<pin name="IO17" x="20.32" y="-2.54" length="middle" rot="R180"/>
<pin name="IO5" x="20.32" y="0" length="middle" rot="R180"/>
<pin name="IO18" x="20.32" y="2.54" length="middle" rot="R180"/>
<pin name="IO19" x="20.32" y="5.08" length="middle" rot="R180"/>
<pin name="GND2" x="20.32" y="7.62" length="middle" direction="pwr" rot="R180"/>
<pin name="IO21" x="20.32" y="10.16" length="middle" rot="R180"/>
<pin name="RXD0" x="20.32" y="12.7" length="middle" direction="in" rot="R180"/>
<pin name="TXD0" x="20.32" y="15.24" length="middle" direction="out" rot="R180"/>
<pin name="IO22" x="20.32" y="17.78" length="middle" rot="R180"/>
<pin name="IO23" x="20.32" y="20.32" length="middle" rot="R180"/>
<pin name="GND3" x="20.32" y="22.86" length="middle" direction="pwr" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="ESP32-DEVKITC-32D" prefix="U">
<description>Eval Board For Esp-Wroom-32 &lt;a href="https://pricing.snapeda.com/parts/ESP32-DEVKITC-32D/Espressif%20Systems/view-part?ref=eda"&gt;Check availability&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="ESP32-DEVKITC-32D" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MODULE_ESP32-DEVKITC-32D">
<connects>
<connect gate="G$1" pin="3V3" pad="1"/>
<connect gate="G$1" pin="CLK" pad="38"/>
<connect gate="G$1" pin="CMD" pad="18"/>
<connect gate="G$1" pin="EN" pad="2"/>
<connect gate="G$1" pin="EXT_5V" pad="19"/>
<connect gate="G$1" pin="GND1" pad="14"/>
<connect gate="G$1" pin="GND2" pad="26"/>
<connect gate="G$1" pin="GND3" pad="20"/>
<connect gate="G$1" pin="IO0" pad="33"/>
<connect gate="G$1" pin="IO12" pad="13"/>
<connect gate="G$1" pin="IO13" pad="15"/>
<connect gate="G$1" pin="IO14" pad="12"/>
<connect gate="G$1" pin="IO15" pad="35"/>
<connect gate="G$1" pin="IO16" pad="31"/>
<connect gate="G$1" pin="IO17" pad="30"/>
<connect gate="G$1" pin="IO18" pad="28"/>
<connect gate="G$1" pin="IO19" pad="27"/>
<connect gate="G$1" pin="IO2" pad="34"/>
<connect gate="G$1" pin="IO21" pad="25"/>
<connect gate="G$1" pin="IO22" pad="22"/>
<connect gate="G$1" pin="IO23" pad="21"/>
<connect gate="G$1" pin="IO25" pad="9"/>
<connect gate="G$1" pin="IO26" pad="10"/>
<connect gate="G$1" pin="IO27" pad="11"/>
<connect gate="G$1" pin="IO32" pad="7"/>
<connect gate="G$1" pin="IO33" pad="8"/>
<connect gate="G$1" pin="IO34" pad="5"/>
<connect gate="G$1" pin="IO35" pad="6"/>
<connect gate="G$1" pin="IO4" pad="32"/>
<connect gate="G$1" pin="IO5" pad="29"/>
<connect gate="G$1" pin="RXD0" pad="24"/>
<connect gate="G$1" pin="SD0" pad="37"/>
<connect gate="G$1" pin="SD1" pad="36"/>
<connect gate="G$1" pin="SD2" pad="16"/>
<connect gate="G$1" pin="SD3" pad="17"/>
<connect gate="G$1" pin="SENSOR_VN" pad="4"/>
<connect gate="G$1" pin="SENSOR_VP" pad="3"/>
<connect gate="G$1" pin="TXD0" pad="23"/>
</connects>
<technologies>
<technology name="">
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="DESCRIPTION" value=" WiFi Development Tools (802.11) ESP32 General Development Kit, ESP32-WROOM-32D on the board "/>
<attribute name="MF" value="Espressif Systems"/>
<attribute name="MP" value="ESP32-DEVKITC-32D"/>
<attribute name="PACKAGE" value="None"/>
<attribute name="PRICE" value="None"/>
<attribute name="PURCHASE-URL" value="https://pricing.snapeda.com/search/part/ESP32-DEVKITC-32D/?ref=eda"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="S2B-XH-A_LF__SN_">
<packages>
<package name="JST_S2B-XH-A(LF)(SN)">
<wire x1="-3.7" y1="9.2" x2="3.7" y2="9.2" width="0.127" layer="21"/>
<wire x1="3.7" y1="9.2" x2="3.7" y2="-2.3" width="0.127" layer="21"/>
<wire x1="3.7" y1="-2.3" x2="-3.7" y2="-2.3" width="0.127" layer="21"/>
<wire x1="-3.7" y1="-2.3" x2="-3.7" y2="9.2" width="0.127" layer="21"/>
<wire x1="-4" y1="9.5" x2="4" y2="9.5" width="0.127" layer="39"/>
<wire x1="4" y1="9.5" x2="4" y2="-2.6" width="0.127" layer="39"/>
<wire x1="4" y1="-2.6" x2="-4" y2="-2.6" width="0.127" layer="39"/>
<wire x1="-4" y1="-2.6" x2="-4" y2="9.5" width="0.127" layer="39"/>
<text x="-4.10343125" y="9.60803125" size="1.271059375" layer="25">&gt;NAME</text>
<text x="-4.105309375" y="-4.00518125" size="1.27165" layer="27">&gt;VALUE</text>
<circle x="-4.5" y="0.5" radius="0.254" width="0" layer="21"/>
<pad name="1" x="-1.25" y="0" drill="1" shape="square"/>
<pad name="2" x="1.25" y="0" drill="1"/>
</package>
</packages>
<symbols>
<symbol name="S2B-XH-A(LF)(SN)">
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="1.27" width="0.254" layer="94"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.54" x2="-2.54" y2="2.54" width="0.254" layer="94"/>
<text x="-2.543990625" y="2.543990625" size="1.272" layer="95">&gt;NAME</text>
<text x="-2.543290625" y="-3.814940625" size="1.27165" layer="96">&gt;VALUE</text>
<wire x1="-2.54" y1="1.27" x2="0" y2="1.27" width="0.762" layer="94"/>
<wire x1="-2.54" y1="-1.27" x2="0" y2="-1.27" width="0.762" layer="94"/>
<pin name="1" x="-7.62" y="1.27" length="middle" direction="pas"/>
<pin name="2" x="-7.62" y="-1.27" length="middle" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="S2B-XH-A(LF)(SN)" prefix="P">
<description>XH Series 2.5mm 2 Position Through Hole Shrouded Header Connector &lt;a href="https://pricing.snapeda.com/parts/S2B-XH-A%28LF%29%28SN%29/JST%20Sales/view-part?ref=eda"&gt;Check availability&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="S2B-XH-A(LF)(SN)" x="0" y="0"/>
</gates>
<devices>
<device name="" package="JST_S2B-XH-A(LF)(SN)">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="DESCRIPTION" value=" Connector Header Through Hole, Right Angle 2 position 0.098 (2.50mm) "/>
<attribute name="MF" value="JST Sales"/>
<attribute name="MP" value="S2B-XH-A(LF)(SN)"/>
<attribute name="PACKAGE" value="None"/>
<attribute name="PRICE" value="None"/>
<attribute name="PURCHASE-URL" value="https://pricing.snapeda.com/search/part/S2B-XH-A(LF)(SN)/?ref=eda"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="S3B-XH-A_LF__SN_">
<packages>
<package name="JST_S3B-XH-A(LF)(SN)">
<wire x1="-4.95" y1="5.75" x2="4.95" y2="5.75" width="0.127" layer="51"/>
<wire x1="4.95" y1="5.75" x2="4.95" y2="-5.75" width="0.127" layer="51"/>
<wire x1="4.95" y1="-5.75" x2="-4.95" y2="-5.75" width="0.127" layer="51"/>
<wire x1="-4.95" y1="-5.75" x2="-4.95" y2="5.75" width="0.127" layer="51"/>
<wire x1="-5.2" y1="6" x2="5.2" y2="6" width="0.05" layer="39"/>
<wire x1="5.2" y1="6" x2="5.2" y2="-6" width="0.05" layer="39"/>
<wire x1="5.2" y1="-6" x2="-5.2" y2="-6" width="0.05" layer="39"/>
<wire x1="-5.2" y1="-6" x2="-5.2" y2="6" width="0.05" layer="39"/>
<text x="-5" y="6.55" size="1.27" layer="25">&gt;NAME</text>
<text x="-5" y="-6.45" size="1.27" layer="27" align="top-left">&gt;VALUE</text>
<circle x="2.5" y="-6.45" radius="0.1" width="0.2" layer="51"/>
<wire x1="-4.95" y1="5.75" x2="4.95" y2="5.75" width="0.127" layer="21"/>
<wire x1="4.95" y1="5.75" x2="4.95" y2="-5.75" width="0.127" layer="21"/>
<wire x1="4.95" y1="-5.75" x2="-4.95" y2="-5.75" width="0.127" layer="21"/>
<wire x1="-4.95" y1="-5.75" x2="-4.95" y2="5.75" width="0.127" layer="21"/>
<circle x="2.5" y="-6.45" radius="0.1" width="0.2" layer="21"/>
<pad name="1" x="2.5" y="-3.45" drill="1" shape="square" rot="R180"/>
<pad name="2" x="0" y="-3.45" drill="1" rot="R180"/>
<pad name="3" x="-2.5" y="-3.45" drill="1" rot="R180"/>
</package>
</packages>
<symbols>
<symbol name="S3B-XH-A(LF)(SN)">
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<text x="-5.08" y="6.35" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-10.16" y="2.54" length="middle" direction="pas"/>
<pin name="2" x="-10.16" y="0" length="middle" direction="pas"/>
<pin name="3" x="-10.16" y="-2.54" length="middle" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="S3B-XH-A(LF)(SN)" prefix="J">
<description>Connector Header Through Hole, Right Angle 3 position 0.098" (2.50mm) &lt;a href="https://pricing.snapeda.com/parts/S3B-XH-A%28LF%29%28SN%29/JST%20Sales%20America%20Inc./view-part?ref=eda"&gt;Check availability&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="S3B-XH-A(LF)(SN)" x="0" y="0"/>
</gates>
<devices>
<device name="" package="JST_S3B-XH-A(LF)(SN)">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="DESCRIPTION" value=" Connector Header Through Hole, Right Angle 3 position 0.098 (2.50mm) "/>
<attribute name="MF" value="JST Sales America Inc."/>
<attribute name="MP" value="S3B-XH-A(LF)(SN)"/>
<attribute name="PACKAGE" value="Custom Package JST Sales"/>
<attribute name="PRICE" value="None"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="LD1117">
<packages>
<package name="TO220">
<wire x1="4.826" y1="-1.778" x2="5.08" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="4.826" y1="-1.778" x2="-4.826" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.524" x2="-4.826" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.397" x2="5.08" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.524" x2="-5.08" y2="1.397" width="0.1524" layer="21"/>
<circle x="-4.6228" y="-1.1684" radius="0.254" width="0" layer="21"/>
<text x="-5.08798125" y="-3.179990625" size="0.814075" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08153125" y="-4.446340625" size="0.81304375" layer="27" ratio="10">&gt;VALUE</text>
<text x="-3.177" y="-1.2708" size="1.2708" layer="51" ratio="10">1</text>
<text x="-0.635815625" y="-1.27163125" size="1.27163125" layer="51" ratio="10">2</text>
<text x="1.90583125" y="-1.270559375" size="1.270559375" layer="51" ratio="10">3</text>
<rectangle x1="-5.334790625" y1="1.270190625" x2="-3.429" y2="2.54" layer="21"/>
<rectangle x1="-3.429509375" y1="1.77826875" x2="-1.651" y2="2.54" layer="21"/>
<rectangle x1="-1.651559375" y1="1.27043125" x2="-0.889" y2="2.54" layer="21"/>
<rectangle x1="-0.8901" y1="1.7802" x2="0.889" y2="2.54" layer="21"/>
<rectangle x1="0.890746875" y1="1.2725" x2="1.651" y2="2.54" layer="21"/>
<rectangle x1="1.653409375" y1="1.780590625" x2="3.429" y2="2.54" layer="21"/>
<rectangle x1="3.4324" y1="1.271259375" x2="5.334" y2="2.54" layer="21"/>
<rectangle x1="-3.430009375" y1="1.27038125" x2="-1.651" y2="1.778" layer="51"/>
<rectangle x1="-0.89071875" y1="1.27245" x2="0.889" y2="1.778" layer="51"/>
<rectangle x1="1.65143125" y1="1.27033125" x2="3.429" y2="1.778" layer="51"/>
<pad name="1" x="-2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="0" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="2.54" y="0" drill="1.016" shape="long" rot="R90"/>
</package>
</packages>
<symbols>
<symbol name="LD1117">
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="5.08" y2="2.54" width="0.4064" layer="94"/>
<wire x1="5.08" y1="2.54" x2="-5.08" y2="2.54" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="2.54" x2="-5.08" y2="-5.08" width="0.4064" layer="94"/>
<text x="2.54066875" y="-7.622" size="1.77846875" layer="95">&gt;NAME</text>
<text x="2.543859375" y="-10.1754" size="1.7807" layer="96">&gt;VALUE</text>
<text x="-2.03296875" y="-4.32006875" size="1.52473125" layer="95">GND</text>
<text x="-4.447609375" y="-0.635371875" size="1.524890625" layer="95">IN</text>
<text x="0.636234375" y="-0.636234375" size="1.526959375" layer="95">OUT</text>
<pin name="IN" x="-7.62" y="0" visible="off" length="short" direction="in"/>
<pin name="GND" x="0" y="-7.62" visible="off" length="short" direction="in" rot="R90"/>
<pin name="OUT" x="7.62" y="0" visible="off" length="short" direction="out" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="LD1117">
<description> &lt;a href="https://pricing.snapeda.com/parts/LD1117/STMicroelectronics/view-part?ref=eda"&gt;Check availability&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="LD1117" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TO220">
<connects>
<connect gate="G$1" pin="GND" pad="1"/>
<connect gate="G$1" pin="IN" pad="3"/>
<connect gate="G$1" pin="OUT" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="DESCRIPTION" value=" Linear Voltage Regulator IC Positive Fixed 1 Output 800mA DPAK "/>
<attribute name="MF" value="STMicroelectronics"/>
<attribute name="MP" value="LD1117"/>
<attribute name="PACKAGE" value="None"/>
<attribute name="PRICE" value="None"/>
<attribute name="PURCHASE-URL" value="https://pricing.snapeda.com/search/part/LD1117/?ref=eda"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Capacitors">
<description>&lt;h3&gt;SparkFun Capacitors&lt;/h3&gt;
This library contains capacitors. 
&lt;br&gt;
&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is &lt;b&gt; the end user's responsibility&lt;/b&gt; to ensure correctness and suitablity for a given componet or application. 
&lt;br&gt;
&lt;br&gt;If you enjoy using this library, please buy one of our products at &lt;a href=" www.sparkfun.com"&gt;SparkFun.com&lt;/a&gt;.
&lt;br&gt;
&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;
&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="EIA3216">
<description>Generic EIA 3216 (1206) polarized tantalum capacitor</description>
<wire x1="-1" y1="-1.2" x2="-2.5" y2="-1.2" width="0.2032" layer="51"/>
<wire x1="-2.5" y1="-1.2" x2="-2.5" y2="1.2" width="0.2032" layer="51"/>
<wire x1="-2.5" y1="1.2" x2="-1" y2="1.2" width="0.2032" layer="51"/>
<wire x1="1" y1="-1.2" x2="2.1" y2="-1.2" width="0.2032" layer="51"/>
<wire x1="2.1" y1="-1.2" x2="2.5" y2="-0.8" width="0.2032" layer="51"/>
<wire x1="2.5" y1="-0.8" x2="2.5" y2="0.8" width="0.2032" layer="51"/>
<wire x1="2.5" y1="0.8" x2="2.1" y2="1.2" width="0.2032" layer="51"/>
<wire x1="2.1" y1="1.2" x2="1" y2="1.2" width="0.2032" layer="51"/>
<wire x1="2.413" y1="0.762" x2="2.413" y2="-0.762" width="0.2032" layer="21"/>
<smd name="-" x="-1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<smd name="+" x="1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<text x="0" y="1.143" size="0.6096" layer="25" font="vector" ratio="20" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.143" size="0.6096" layer="27" font="vector" ratio="20" align="top-center">&gt;VALUE</text>
<wire x1="-2.286" y1="0.9906" x2="2.286" y2="0.9906" width="0.0508" layer="39"/>
<wire x1="2.286" y1="0.9906" x2="2.286" y2="-0.9906" width="0.0508" layer="39"/>
<wire x1="2.286" y1="-0.9906" x2="-2.286" y2="-0.9906" width="0.0508" layer="39"/>
<wire x1="-2.286" y1="-0.9906" x2="-2.286" y2="0.9906" width="0.0508" layer="39"/>
</package>
<package name="0603-POLAR">
<description>&lt;p&gt;&lt;b&gt;Polarized 1608 (0603) package&lt;/b&gt;&lt;/p&gt;
&lt;p&gt;0.2mm courtyard excess rounded to nearest 0.05mm.&lt;/p&gt;</description>
<wire x1="-1.1" y1="-0.8" x2="-1.7" y2="-0.8" width="0.2032" layer="51"/>
<wire x1="-1.7" y1="-0.8" x2="-1.7" y2="0.8" width="0.2032" layer="51"/>
<wire x1="-1.7" y1="0.8" x2="-1.1" y2="0.8" width="0.2032" layer="51"/>
<wire x1="1.1" y1="-0.8" x2="1.5" y2="-0.8" width="0.2032" layer="51"/>
<wire x1="1.5" y1="-0.8" x2="1.9" y2="-0.4" width="0.2032" layer="51"/>
<wire x1="1.9" y1="-0.4" x2="1.9" y2="0.4" width="0.2032" layer="51"/>
<wire x1="1.9" y1="0.4" x2="1.5" y2="0.8" width="0.2032" layer="51"/>
<wire x1="1.5" y1="0.8" x2="1.1" y2="0.8" width="0.2032" layer="51"/>
<wire x1="-1.6" y1="0.7" x2="1.6" y2="0.7" width="0.0508" layer="39"/>
<wire x1="1.6" y1="0.7" x2="1.6" y2="-0.7" width="0.0508" layer="39"/>
<wire x1="1.6" y1="-0.7" x2="-1.6" y2="-0.7" width="0.0508" layer="39"/>
<wire x1="-1.6" y1="-0.7" x2="-1.6" y2="0.7" width="0.0508" layer="39"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<smd name="-" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="+" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="0" y="0.762" size="0.6096" layer="25" font="vector" ratio="20" align="bottom-center">&gt;NAME</text>
<text x="0" y="-0.762" size="0.6096" layer="27" font="vector" ratio="20" align="top-center">&gt;VALUE</text>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<wire x1="1.651" y1="0.508" x2="1.651" y2="-0.508" width="0.2032" layer="21"/>
</package>
<package name="EIA3528">
<description>Generic EIA 3528 polarized tantalum capacitor</description>
<wire x1="-0.9" y1="-1.6" x2="-2.6" y2="-1.6" width="0.2032" layer="51"/>
<wire x1="-2.6" y1="-1.6" x2="-2.6" y2="1.55" width="0.2032" layer="51"/>
<wire x1="-2.6" y1="1.55" x2="-0.9" y2="1.55" width="0.2032" layer="51"/>
<wire x1="1" y1="-1.55" x2="2.2" y2="-1.55" width="0.2032" layer="51"/>
<wire x1="2.2" y1="-1.55" x2="2.6" y2="-1.2" width="0.2032" layer="51"/>
<wire x1="2.6" y1="-1.2" x2="2.6" y2="1.25" width="0.2032" layer="51"/>
<wire x1="2.6" y1="1.25" x2="2.2" y2="1.55" width="0.2032" layer="51"/>
<wire x1="2.2" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="51"/>
<wire x1="2.641" y1="1.311" x2="2.641" y2="-1.286" width="0.2032" layer="21" style="longdash"/>
<smd name="C" x="-1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<smd name="A" x="1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<text x="0" y="1.778" size="0.6096" layer="25" font="vector" ratio="20" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.778" size="0.6096" layer="27" font="vector" ratio="20" align="top-center">&gt;VALUE</text>
</package>
<package name="CPOL-RADIAL-2.5MM-5MM">
<description>2.5 mm spaced PTHs with 5 mm diameter outline and standard solder mask</description>
<pad name="1" x="1.25" y="0" drill="0.7" diameter="1.651" shape="square"/>
<pad name="2" x="-1.25" y="0" drill="0.7" diameter="1.651"/>
<circle x="0" y="0" radius="2.5" width="0.2032" layer="21"/>
<text x="0" y="2.667" size="0.6096" layer="25" font="vector" ratio="20" align="bottom-center">&gt;Name</text>
<text x="0" y="-2.667" size="0.6096" layer="27" font="vector" ratio="20" align="top-center">&gt;Value</text>
<wire x1="-0.742" y1="1.397" x2="-1.758" y2="1.397" width="0.2032" layer="21"/>
<wire x1="1.758" y1="1.397" x2="0.742" y2="1.397" width="0.2032" layer="21"/>
<wire x1="1.25" y1="1.905" x2="1.25" y2="0.889" width="0.2032" layer="21"/>
</package>
<package name="CPOL-RADIAL-2.5MM-5MM-KIT">
<description>2.5 mm spaced PTHs with top copper masked</description>
<circle x="0" y="0" radius="2.5" width="0.2032" layer="21"/>
<pad name="1" x="1.25" y="0" drill="0.7" diameter="1.651" shape="square" stop="no"/>
<pad name="2" x="-1.25" y="0" drill="0.7" diameter="1.651" stop="no"/>
<text x="0" y="2.667" size="0.6096" layer="25" font="vector" ratio="20" align="bottom-center">&gt;Name</text>
<text x="0" y="-2.667" size="0.6096" layer="27" font="vector" ratio="20" align="top-center">&gt;Value</text>
<circle x="-1.25" y="0" radius="0.3556" width="0" layer="29"/>
<circle x="-1.25" y="0" radius="0.9652" width="0" layer="30"/>
<circle x="1.25" y="0" radius="0.3556" width="0" layer="29"/>
<rectangle x1="0.2848" y1="-0.9652" x2="2.2152" y2="0.9652" layer="30"/>
<wire x1="-0.742" y1="1.397" x2="-1.758" y2="1.397" width="0.2032" layer="21"/>
<wire x1="1.758" y1="1.397" x2="0.742" y2="1.397" width="0.2032" layer="21"/>
<wire x1="1.25" y1="1.905" x2="1.25" y2="0.889" width="0.2032" layer="21"/>
</package>
<package name="EIA6032-NOM">
<description>Metric Size Code EIA 6032-25 Median (Nominal) Land Protrusion&lt;br /&gt;
http://www.kemet.com/Lists/ProductCatalog/Attachments/254/KEM_T2005_T491.pdf</description>
<wire x1="-3.91" y1="1.5" x2="-2" y2="1.5" width="0.127" layer="51"/>
<wire x1="-3.91" y1="1.5" x2="-3.91" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-3.91" y1="-1.5" x2="-2" y2="-1.5" width="0.127" layer="51"/>
<wire x1="2" y1="1.5" x2="3.5" y2="1.5" width="0.127" layer="51"/>
<wire x1="3.5" y1="1.5" x2="3.91" y2="1" width="0.127" layer="51"/>
<wire x1="3.91" y1="1" x2="3.91" y2="-1" width="0.127" layer="51"/>
<wire x1="3.91" y1="-1" x2="3.5" y2="-1.5" width="0.127" layer="51"/>
<wire x1="3.5" y1="-1.5" x2="2" y2="-1.5" width="0.127" layer="51"/>
<smd name="C" x="-2.47" y="0" dx="2.37" dy="2.23" layer="1" rot="R180"/>
<smd name="A" x="2.47" y="0" dx="2.37" dy="2.23" layer="1" rot="R180"/>
<text x="0" y="1.27" size="0.6096" layer="25" font="vector" ratio="20" align="bottom-center">&gt;Name</text>
<text x="0" y="-1.27" size="0.6096" layer="27" font="vector" ratio="20" align="top-center">&gt;Value</text>
<wire x1="3.91" y1="1" x2="3.91" y2="-1" width="0.127" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="CAP_POL">
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-1.016" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-1" x2="2.4892" y2="-1.8542" width="0.254" layer="94" curve="-37.878202" cap="flat"/>
<wire x1="-2.4669" y1="-1.8504" x2="0" y2="-1.0161" width="0.254" layer="94" curve="-37.376341" cap="flat"/>
<text x="1.016" y="0.635" size="1.778" layer="95" font="vector">&gt;NAME</text>
<text x="1.016" y="-4.191" size="1.778" layer="96" font="vector">&gt;VALUE</text>
<rectangle x1="-2.253" y1="0.668" x2="-1.364" y2="0.795" layer="94"/>
<rectangle x1="-1.872" y1="0.287" x2="-1.745" y2="1.176" layer="94"/>
<pin name="+" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="-" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="10UF-POLAR" prefix="C">
<description>&lt;h3&gt;10.0µF polarized capacitors&lt;/h3&gt;
&lt;p&gt;A capacitor is a passive two-terminal electrical component used to store electrical energy temporarily in an electric field.&lt;/p&gt;</description>
<gates>
<gate name="G$1" symbol="CAP_POL" x="0" y="0"/>
</gates>
<devices>
<device name="-EIA3216-16V-10%(TANT)" package="EIA3216">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CAP-00811"/>
<attribute name="VALUE" value="10uF"/>
</technology>
</technologies>
</device>
<device name="-0603-6.3V-20%(TANT)" package="0603-POLAR">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CAP-13210"/>
<attribute name="VALUE" value="10uF"/>
</technology>
</technologies>
</device>
<device name="-EIA3528-20V-10%(TANT)" package="EIA3528">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CAP-08063"/>
<attribute name="VALUE" value="10uF"/>
</technology>
</technologies>
</device>
<device name="-RADIAL-2.5MM-25V-20%" package="CPOL-RADIAL-2.5MM-5MM">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CAP-08440"/>
<attribute name="VALUE" value="10uF"/>
</technology>
</technologies>
</device>
<device name="-RADIAL-2.5MM-KIT-25V-20%" package="CPOL-RADIAL-2.5MM-5MM-KIT">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CAP-08440"/>
<attribute name="VALUE" value="10uF"/>
</technology>
</technologies>
</device>
<device name="-EIA6032-25V-10%" package="EIA6032-NOM">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CAP-12984"/>
<attribute name="VALUE" value="10µF"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply2" urn="urn:adsk.eagle:library:372">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
Please keep in mind, that these devices are necessary for the
automatic wiring of the supply signals.&lt;p&gt;
The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND" urn="urn:adsk.eagle:symbol:26990/1" library_version="2">
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<text x="-1.905" y="-3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" urn="urn:adsk.eagle:component:27037/1" prefix="SUPPLY" library_version="2">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="GND" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0.254" drill="0">
</class>
</classes>
<parts>
<part name="U1" library="ESP32-DEVKITC-32D" deviceset="ESP32-DEVKITC-32D" device=""/>
<part name="P1" library="S2B-XH-A_LF__SN_" deviceset="S2B-XH-A(LF)(SN)" device=""/>
<part name="J1" library="S3B-XH-A_LF__SN_" deviceset="S3B-XH-A(LF)(SN)" device=""/>
<part name="J2" library="S3B-XH-A_LF__SN_" deviceset="S3B-XH-A(LF)(SN)" device=""/>
<part name="J3" library="S3B-XH-A_LF__SN_" deviceset="S3B-XH-A(LF)(SN)" device=""/>
<part name="J4" library="S3B-XH-A_LF__SN_" deviceset="S3B-XH-A(LF)(SN)" device=""/>
<part name="J5" library="S3B-XH-A_LF__SN_" deviceset="S3B-XH-A(LF)(SN)" device=""/>
<part name="J6" library="S3B-XH-A_LF__SN_" deviceset="S3B-XH-A(LF)(SN)" device=""/>
<part name="J7" library="S3B-XH-A_LF__SN_" deviceset="S3B-XH-A(LF)(SN)" device=""/>
<part name="J8" library="S3B-XH-A_LF__SN_" deviceset="S3B-XH-A(LF)(SN)" device=""/>
<part name="U$1" library="LD1117" deviceset="LD1117" device=""/>
<part name="C1" library="SparkFun-Capacitors" deviceset="10UF-POLAR" device="-RADIAL-2.5MM-25V-20%" value="100nF"/>
<part name="C2" library="SparkFun-Capacitors" deviceset="10UF-POLAR" device="-RADIAL-2.5MM-25V-20%" value="10uF"/>
<part name="SUPPLY1" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U1" gate="G$1" x="40.64" y="38.1" smashed="yes">
<attribute name="NAME" x="25.3828" y="64.1643" size="1.78" layer="95"/>
<attribute name="VALUE" x="25.3837" y="10.1302" size="1.7799" layer="96"/>
</instance>
<instance part="P1" gate="G$1" x="114.3" y="99.06" smashed="yes">
<attribute name="NAME" x="111.756009375" y="101.603990625" size="1.272" layer="95"/>
<attribute name="VALUE" x="111.756709375" y="95.245059375" size="1.27165" layer="96"/>
</instance>
<instance part="J1" gate="G$1" x="116.84" y="81.28" smashed="yes">
<attribute name="NAME" x="111.76" y="87.63" size="1.778" layer="95"/>
<attribute name="VALUE" x="111.76" y="73.66" size="1.778" layer="96"/>
</instance>
<instance part="J2" gate="G$1" x="116.84" y="63.5" smashed="yes">
<attribute name="NAME" x="111.76" y="69.85" size="1.778" layer="95"/>
<attribute name="VALUE" x="111.76" y="55.88" size="1.778" layer="96"/>
</instance>
<instance part="J3" gate="G$1" x="116.84" y="43.18" smashed="yes">
<attribute name="NAME" x="111.76" y="49.53" size="1.778" layer="95"/>
<attribute name="VALUE" x="111.76" y="35.56" size="1.778" layer="96"/>
</instance>
<instance part="J4" gate="G$1" x="116.84" y="22.86" smashed="yes">
<attribute name="NAME" x="111.76" y="29.21" size="1.778" layer="95"/>
<attribute name="VALUE" x="111.76" y="15.24" size="1.778" layer="96"/>
</instance>
<instance part="J5" gate="G$1" x="165.1" y="81.28" smashed="yes">
<attribute name="NAME" x="160.02" y="87.63" size="1.778" layer="95"/>
<attribute name="VALUE" x="160.02" y="73.66" size="1.778" layer="96"/>
</instance>
<instance part="J6" gate="G$1" x="165.1" y="63.5" smashed="yes">
<attribute name="NAME" x="160.02" y="69.85" size="1.778" layer="95"/>
<attribute name="VALUE" x="160.02" y="55.88" size="1.778" layer="96"/>
</instance>
<instance part="J7" gate="G$1" x="165.1" y="43.18" smashed="yes">
<attribute name="NAME" x="160.02" y="49.53" size="1.778" layer="95"/>
<attribute name="VALUE" x="160.02" y="35.56" size="1.778" layer="96"/>
</instance>
<instance part="J8" gate="G$1" x="165.1" y="22.86" smashed="yes">
<attribute name="NAME" x="160.02" y="29.21" size="1.778" layer="95"/>
<attribute name="VALUE" x="160.02" y="15.24" size="1.778" layer="96"/>
</instance>
<instance part="U$1" gate="G$1" x="25.4" y="99.06" smashed="yes">
<attribute name="NAME" x="27.94066875" y="91.438" size="1.77846875" layer="95"/>
<attribute name="VALUE" x="27.943859375" y="88.8846" size="1.7807" layer="96"/>
</instance>
<instance part="C1" gate="G$1" x="7.62" y="91.44" smashed="yes">
<attribute name="NAME" x="8.636" y="92.075" size="1.778" layer="95" font="vector"/>
<attribute name="VALUE" x="8.636" y="87.249" size="1.778" layer="96" font="vector"/>
</instance>
<instance part="C2" gate="G$1" x="43.18" y="91.44" smashed="yes">
<attribute name="NAME" x="44.196" y="92.075" size="1.778" layer="95" font="vector"/>
<attribute name="VALUE" x="44.196" y="87.249" size="1.778" layer="96" font="vector"/>
</instance>
<instance part="SUPPLY1" gate="GND" x="25.4" y="78.74" smashed="yes">
<attribute name="VALUE" x="23.495" y="75.565" size="1.778" layer="96"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="GATE" class="0">
<segment>
<pinref part="P1" gate="G$1" pin="1"/>
<wire x1="106.68" y1="100.33" x2="94.234" y2="100.33" width="0.1524" layer="91"/>
<label x="88.9" y="101.6" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO22"/>
<wire x1="60.96" y1="55.88" x2="68.58" y2="55.88" width="0.1524" layer="91"/>
<label x="63.5" y="55.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="OUT1" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="1"/>
<wire x1="106.68" y1="83.82" x2="93.98" y2="83.82" width="0.1524" layer="91"/>
<label x="93.98" y="83.82" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO12"/>
<wire x1="20.32" y1="30.48" x2="10.16" y2="30.48" width="0.1524" layer="91"/>
<label x="10.16" y="30.48" size="1.778" layer="95"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="2"/>
<wire x1="106.68" y1="81.28" x2="93.98" y2="81.28" width="0.1524" layer="91"/>
<label x="93.98" y="81.28" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="2"/>
<wire x1="106.68" y1="63.5" x2="93.98" y2="63.5" width="0.1524" layer="91"/>
<label x="93.98" y="63.5" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J3" gate="G$1" pin="2"/>
<wire x1="106.68" y1="43.18" x2="93.98" y2="43.18" width="0.1524" layer="91"/>
<label x="93.98" y="43.18" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="2"/>
<wire x1="106.68" y1="22.86" x2="93.98" y2="22.86" width="0.1524" layer="91"/>
<label x="93.98" y="22.86" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J5" gate="G$1" pin="2"/>
<wire x1="154.94" y1="81.28" x2="142.24" y2="81.28" width="0.1524" layer="91"/>
<label x="142.24" y="81.28" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J6" gate="G$1" pin="2"/>
<wire x1="154.94" y1="63.5" x2="142.24" y2="63.5" width="0.1524" layer="91"/>
<label x="142.24" y="63.5" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="2"/>
<wire x1="154.94" y1="43.18" x2="142.24" y2="43.18" width="0.1524" layer="91"/>
<label x="142.24" y="43.18" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J8" gate="G$1" pin="2"/>
<wire x1="154.94" y1="22.86" x2="142.24" y2="22.86" width="0.1524" layer="91"/>
<label x="142.24" y="22.86" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="P1" gate="G$1" pin="2"/>
<wire x1="106.68" y1="97.79" x2="93.98" y2="97.79" width="0.1524" layer="91"/>
<label x="88.9" y="96.52" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="GND"/>
<wire x1="25.4" y1="91.44" x2="25.4" y2="81.28" width="0.1524" layer="91"/>
<wire x1="25.4" y1="81.28" x2="7.62" y2="81.28" width="0.1524" layer="91"/>
<pinref part="C1" gate="G$1" pin="-"/>
<wire x1="7.62" y1="81.28" x2="7.62" y2="86.36" width="0.1524" layer="91"/>
<pinref part="C2" gate="G$1" pin="-"/>
<wire x1="43.18" y1="86.36" x2="43.18" y2="81.28" width="0.1524" layer="91"/>
<wire x1="43.18" y1="81.28" x2="25.4" y2="81.28" width="0.1524" layer="91"/>
<junction x="25.4" y="81.28"/>
<pinref part="SUPPLY1" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="GND3"/>
<wire x1="60.96" y1="60.96" x2="68.58" y2="60.96" width="0.1524" layer="91"/>
<label x="63.5" y="60.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="GND2"/>
<wire x1="60.96" y1="45.72" x2="68.58" y2="45.72" width="0.1524" layer="91"/>
<label x="63.5" y="45.72" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="GND1"/>
<wire x1="20.32" y1="27.94" x2="10.16" y2="27.94" width="0.1524" layer="91"/>
<label x="10.16" y="27.94" size="1.778" layer="95"/>
</segment>
</net>
<net name="OUT2" class="0">
<segment>
<pinref part="J2" gate="G$1" pin="1"/>
<wire x1="106.68" y1="66.04" x2="93.98" y2="66.04" width="0.1524" layer="91"/>
<label x="93.98" y="66.04" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO14"/>
<wire x1="20.32" y1="33.02" x2="10.16" y2="33.02" width="0.1524" layer="91"/>
<label x="10.16" y="33.02" size="1.778" layer="95"/>
</segment>
</net>
<net name="OUT3" class="0">
<segment>
<pinref part="J3" gate="G$1" pin="1"/>
<wire x1="106.68" y1="45.72" x2="93.98" y2="45.72" width="0.1524" layer="91"/>
<label x="93.98" y="45.72" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO27"/>
<wire x1="20.32" y1="35.56" x2="10.16" y2="35.56" width="0.1524" layer="91"/>
<label x="10.16" y="35.56" size="1.778" layer="95"/>
</segment>
</net>
<net name="OUT4" class="0">
<segment>
<pinref part="J4" gate="G$1" pin="1"/>
<wire x1="106.68" y1="25.4" x2="93.98" y2="25.4" width="0.1524" layer="91"/>
<label x="93.98" y="25.4" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO26"/>
<wire x1="20.32" y1="38.1" x2="10.16" y2="38.1" width="0.1524" layer="91"/>
<label x="10.16" y="38.1" size="1.778" layer="95"/>
</segment>
</net>
<net name="OUT5" class="0">
<segment>
<pinref part="J5" gate="G$1" pin="1"/>
<wire x1="154.94" y1="83.82" x2="142.24" y2="83.82" width="0.1524" layer="91"/>
<label x="142.24" y="83.82" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO25"/>
<wire x1="20.32" y1="40.64" x2="10.16" y2="40.64" width="0.1524" layer="91"/>
<label x="10.16" y="40.64" size="1.778" layer="95"/>
</segment>
</net>
<net name="OUT6" class="0">
<segment>
<pinref part="J6" gate="G$1" pin="1"/>
<wire x1="154.94" y1="66.04" x2="142.24" y2="66.04" width="0.1524" layer="91"/>
<label x="142.24" y="66.04" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO33"/>
<wire x1="20.32" y1="43.18" x2="10.16" y2="43.18" width="0.1524" layer="91"/>
<label x="10.16" y="43.18" size="1.778" layer="95"/>
</segment>
</net>
<net name="OUT7" class="0">
<segment>
<pinref part="J7" gate="G$1" pin="1"/>
<wire x1="154.94" y1="45.72" x2="142.24" y2="45.72" width="0.1524" layer="91"/>
<label x="142.24" y="45.72" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO32"/>
<wire x1="20.32" y1="45.72" x2="10.16" y2="45.72" width="0.1524" layer="91"/>
<label x="10.16" y="45.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="OUT8" class="0">
<segment>
<pinref part="J8" gate="G$1" pin="1"/>
<wire x1="154.94" y1="25.4" x2="142.24" y2="25.4" width="0.1524" layer="91"/>
<label x="142.24" y="25.4" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="IO23"/>
<wire x1="60.96" y1="58.42" x2="68.58" y2="58.42" width="0.1524" layer="91"/>
<label x="63.5" y="58.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="USB_5V" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="EXT_5V"/>
<wire x1="20.32" y1="15.24" x2="10.16" y2="15.24" width="0.1524" layer="91"/>
<label x="10.16" y="15.24" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="C1" gate="G$1" pin="+"/>
<pinref part="U$1" gate="G$1" pin="IN"/>
<wire x1="7.62" y1="93.98" x2="7.62" y2="99.06" width="0.1524" layer="91"/>
<wire x1="7.62" y1="99.06" x2="17.78" y2="99.06" width="0.1524" layer="91"/>
<wire x1="7.62" y1="99.06" x2="-2.54" y2="99.06" width="0.1524" layer="91"/>
<junction x="7.62" y="99.06"/>
<label x="-2.54" y="99.06" size="1.778" layer="95"/>
</segment>
</net>
<net name="REG_3V3" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="3"/>
<wire x1="106.68" y1="78.74" x2="93.98" y2="78.74" width="0.1524" layer="91"/>
<label x="93.98" y="78.74" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="3"/>
<wire x1="106.68" y1="60.96" x2="93.98" y2="60.96" width="0.1524" layer="91"/>
<label x="93.98" y="60.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J3" gate="G$1" pin="3"/>
<wire x1="106.68" y1="40.64" x2="93.98" y2="40.64" width="0.1524" layer="91"/>
<label x="93.98" y="40.64" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="3"/>
<wire x1="106.68" y1="20.32" x2="93.98" y2="20.32" width="0.1524" layer="91"/>
<label x="93.98" y="20.32" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J5" gate="G$1" pin="3"/>
<wire x1="154.94" y1="78.74" x2="142.24" y2="78.74" width="0.1524" layer="91"/>
<label x="142.24" y="78.74" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J6" gate="G$1" pin="3"/>
<wire x1="154.94" y1="60.96" x2="142.24" y2="60.96" width="0.1524" layer="91"/>
<label x="142.24" y="60.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="3"/>
<wire x1="154.94" y1="40.64" x2="142.24" y2="40.64" width="0.1524" layer="91"/>
<label x="142.24" y="40.64" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J8" gate="G$1" pin="3"/>
<wire x1="154.94" y1="20.32" x2="142.24" y2="20.32" width="0.1524" layer="91"/>
<label x="142.24" y="20.32" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="OUT"/>
<pinref part="C2" gate="G$1" pin="+"/>
<wire x1="33.02" y1="99.06" x2="43.18" y2="99.06" width="0.1524" layer="91"/>
<wire x1="43.18" y1="99.06" x2="43.18" y2="93.98" width="0.1524" layer="91"/>
<wire x1="43.18" y1="99.06" x2="53.34" y2="99.06" width="0.1524" layer="91"/>
<junction x="43.18" y="99.06"/>
<label x="45.72" y="99.06" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
