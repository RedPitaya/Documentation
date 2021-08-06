How to connect the external clock to RP?
########################################

ADC clock can be provided by:

  * On board 122.88MHz XO (default)
  * From external source / through extension connector (instructions provided bellow)


* Remove: R37, R46
* Add: R34 = 0R, R35 = 0R


 .. figure:: External_img1.png
    :align: center


* Remove: FB11

 .. figure:: External_img2.png
    :align: center


* Remove: 0R on C64, R24
* Add: C64 = 100nF, C63 = 100nF, R36 = 100R

 .. figure:: External_img3.png
    :align: center


 .. figure:: External_shem.png
    :width: 50%
    :align: center


