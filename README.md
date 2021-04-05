# Background_infraredLight_filtering
This repository contains code outlining a method for filtering background infrared light from the input of infrared sensors, using a two-stage sampling process and a fitted 2-dimensional polynomial. The main file, `double_source_data_analysis.ipynb`, contains a complete description of the process, however it is best viewed on Google Colab as there are several images linked from URLs that do not preview here on GitHub. (When viewing the file on Github there should be a link to open it in Colab). The remaining repository structure is:

* `arduino_code`
  * `double_IRsource_data_aquisition.ino`: the arduino file used to gather the data, as described in the Colab notebook.
  * `background_pulse_filter_test_simple.ino`: contains an Arduino implementation of the result that works effectively for real-time background IR light filtering with the WP3DP3BT-BD-P22 phototransistor (using the 2D-polynomial from the notebook).
* `documents`: contains datasheets etc.


Sample of digrams/data visualisations:

<img align="middle" src="/images/basic_IR_filter_process.png" alt="drawing1" width="700"/>

<img align="middle" src="/images/expected_vs_measured_peak.png" alt="drawing1" width="700"/>

<img align="middle" src="/images/IR_source_1_deviation.png" alt="drawing1" width="700"/>

<img align="middle" src="/images/final_line_plot.png" alt="drawing1" width="700"/>
