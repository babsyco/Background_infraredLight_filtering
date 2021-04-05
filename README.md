# Background_infraredLight_filtering
This repository contains code outlining a method for filtering background infrared light from the input of infrared sensors, using a two-stage sampling process and a fitted 2-dimensional polynomial. The main file, `double_source_data_analysis.ipynb`, contains a complete description of the process, however it is best viewed on Google Colab as there are several images linked from URLs that do not preview here on GitHub. (There should be a link to open the notebook on Colab). 

* Hello
  * Hello 

The file `background_pulse_filter_test_simple.ino` contains an Arduino implementation of the result that works effectively in real-time.

Sample of digrams/data visualisations:

<img align="middle" src="/images/basic_IR_filter_process.png" alt="drawing1" width="700"/>

<img align="middle" src="/images/expected_vs_measured_peak.png" alt="drawing1" width="700"/>

<img align="middle" src="/images/IR_source_1_deviation.png" alt="drawing1" width="700"/>

<img align="middle" src="/images/final_line_plot.png" alt="drawing1" width="700"/>
