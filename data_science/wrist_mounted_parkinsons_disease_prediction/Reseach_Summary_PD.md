# Research Summary – Parkinson’s Disease (PD)

Tremor, bradykinesia (i.e., slowness of movement), postural instability and rigidity (i.e., stiffness and resistance to passive movement) are the cardinal motor symptoms of PD.1 In addition, patients also experience non-motor symptoms like dysarthria, hyposmia, sleep disorders, and cognitive impairments. Collectively, these symptoms have a significant impact on the functional ability of patients and their overall quality of life.

---

## Gait analysis and clinical correlations in early Parkinson’s disease
**Source:** https://pmc.ncbi.nlm.nih.gov/articles/PMC5505527/

- Study set out to identify and quantify spatiotemporal and kinematic gait parameters by 3D gait analysis in a group of PD patients compared to control group.
- **Participant size** – 44 early-stage PD patients (23 male & 21 female) - mean age 66.5 ± 9.11 yrs & 44 age and sex-matched healthy participants as the control group (22 male & 22 female) – mean age 67.00 ± 9.42 yrs.

### Findings:
- **Steps per minute:** 102.46 ± 13.17 steps/min in PD patients vs 113.84 ± 4.30 steps/min in control subjects.
- **Stride duration:**  
  - 1.19 ± 0.18 seconds right limb and 1.19 ± 0.19 seconds left limb in PD patients.  
  - 0.426 ± 0.16 seconds right limb and 0.429 ± 0.23 seconds left limb in normal subjects.
- **Stance duration:**  
  - 0.74 ± 0.14 seconds right limb and 0.74 ± 0.16 seconds left limb in PD patients.  
  - 13.4 ± 1.1 seconds right limb and 0.83 ± 0.6 seconds left limb in control subjects.
- Swing phase and swing duration differed considerably too (p<0.05), while the stance phase was not statistically significant in patients compared with healthy subjects.
- **Spatial parameters velocity:**  
  - 0.082 ± 0.29 m/s in PD patients.  
  - 1.33 m/s ± 0.06 in healthy subjects.
- **Step width, stride length and swing velocity:** Highly significant parameters, as was average velocity.
- **Reduced step length:** Reported as one of the key features of PD gait (Yang et al., 2007).
- Results demonstrated that early moderate PD patients showed a reduction of spatiotemporal gait parameters (speed and cadence).
- Loss of balance, short stride and slowness have been found to be the most prevalent clinical features in PD, after exclusively parkinsonian signs (Morris et al., 1994; Morris et al., 1998; Chien et al., 2006; Sofuwa et al., 2005).

---

## Real-World Gait Detection Using a Wrist-Worn Inertial Sensor: Validation Study
**Source:** https://formative.jmir.org/2024/1/e50035/

- Study set out to validate gait sequence (GS) detection algorithms developed for the wrist position against reference data acquired in a real-world context.
- **Participant size** – 83 participants across the health spectrum (PD, MS, heart failure, healthy etc) monitored for 2.5 hours using wrist, lower back and feet sensors. 15 were PD patients.

### Findings:
- In total, 10 algorithms for wrist-based gait detection were validated against a multi sensor reference system and compared to gait detection performance using lower back–worn inertial sensors.
- Algorithms applied to the wrist position can detect GSs with high performance in real-world environments.
- Wrist position is not as accurate as a lower-back position, but significant findings showed a wrist-position still provided accurate information, just at a lower sensitivity.
- Provides evidence that wrist-worn devices can accurately detect changes in gait.

---

## Development of digital biomarkers for resting tremor and bradykinesia using a wrist-worn wearable device
**Source:** https://www.nature.com/articles/s41746-019-0217-7

- This study propose a method that sequentially processes epochs of raw sensor data from a single wrist-worn accelerometer by using heuristic and machine learning models in a hierarchical framework to provide continuous monitoring of tremor and bradykinesia.

### Findings:
- Results show that sensor derived continuous measures of resting tremor and bradykinesia achieve good to strong agreement with clinical assessment of symptom severity and are able to discriminate between treatment-related changes in motor states.
- Approach consists of two steps: Context detection & Symptom severity estimation.
- **Context detection step** includes detection of hand movement followed by detection of gait (if hand movement was detected).  
- **Symptom severity estimation step** includes detection and assessment of resting tremor (if no hand movement was detected) and assessment of bradykinesia (if hand movement was detected and gait was not detected).
- **Hand movement classifier dataset used:** Achieved an accuracy of 92.82% (weighted precision: 93%, recall: 93% and F1 score: 93%) with a false-negative rate of 4.72% and false-positive rate of 10.78%.
- **Gait classifier dataset used:** Achieved an accuracy of 96% (weighted precision: 96%, recall: 96% and F1 score: 96%) with a false-negative rate of 2.45% and false-positive rate of 6.4%.
- **Resting tremor classifier dataset used:** Achieved an accuracy of 83% (weighted precision: 86%, recall: 86% and F1 score: 83%) with a false positive rate of 6.83%.

---

## Using wearables to assess bradykinesia and rigidity in patients with Parkinson's disease: a focused, narrative review of the literature
**Source:** https://www.researchgate.net/publication/333298943_Using_wearables_to_assess_bradykinesia_and_rigidity_in_patients_with_Parkinson%27s_disease_a_focused_narrative_review_of_the_literature

- Literature review to consolidate studies that evaluated objective measurement of bradykinesia and rigidity (31 & 8 studies respectively) within PD patients.

### Findings:
- Several studies reported strong associations between wearable-based measures and the gold-standard references for bradykinesia, and, to a lesser extent, rigidity.

---

## TremorSense: Tremor Detection for Parkinson's Disease Using Convolutional Neural Network
**Source:** https://www.cs.wm.edu/~wsjung/resources/TremorSenseChase.pdf

- Study on TremorSense - a PD tremor detection system/application to classify Parkinson's Disease hand tremors.
- **Participants:** 30 PD patients utilizes accelerometers and gyroscopes as wearable sensors on patients' wrists.

### Findings:
- **Self-Evaluation:** For self-evaluation, the study trained and tested the model using the data from each patient.  
  - Overall precision: 93.31%.  
  - Recall: 100%.  
  - F1 score: 96.54%.  
  - Accuracy: 96.65%.
- **Cross-Evaluation:** Overall precision: 90.64%.  
  - Recall: 100%.  
  - F1 score: 95.09%.  
  - Accuracy: 95.35%.
- **Leave-One-Out Evaluation:** Overall precision: 88.58%.  
  - Recall: 100%.  
  - F1 score: 93.95%.  
  - Accuracy: 94.29%.
- Even though the leave-one-out evaluation accuracy is around 2% worse than self-evaluation, and 1% worse than cross-evaluation, the performance is still strong with an accuracy above 94%.

---

## Parkinson’s Disease Action Tremor Detection with Supervised-Learning Models
**Source:** https://pmc.ncbi.nlm.nih.gov/articles/PMC10516258/

- The study introduces a PD action tremor detection method to recognize PD tremors from regular activities from TremorSense original dataset.
- **Participants:** 30 PD patients wearing accelerometers and gyroscope sensors on their wrists (18 male & 12 females – mean age of 67.43). The data for the TremorSense dataset was collected using two UG sensor bands containing a three-axis accelerometer and a three-axis gyroscope.

### Findings:
- Support Vector Machines (SVMs) perform the best in five-fold cross-validation with over 92% F1 scores. SVMs also show the best performance in the leave-one-out evaluation with over 90% F1 scores.

---

## Datasets
- **Mobilise-d:** https://mobilise-d.eu/data/
