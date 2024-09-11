---
sidebar_position: 1
---
# Modelling of Diabetes for Prediction
Diabetes mellitus is a disease of inadequate control of blood glucose.  Whilst often thought to only have type-1 and type-2 (previously known as 'juvenile' and 'adult onset'); there are actually multiple classifications, including type 1, type 2, maturity-onset diabetes of the young (MODY), gestational diabetes, neonatal diabetes and steroid-induced diabetes[^1]. 

Almost 1.9 million Australians have diabetes, with over 300 developing it every day.  Diabetes is the seventh most common cause of death by disease in Australia, and causes significant complications including blindness, amputations, heart disease and kidney disease [^2].  Approximately 1.3 million people are hospitalised with diabetes-related conditions every year [^3].  

For this; we are looking primarily at type-2 diabetes, as this (and insulin resistance) commonly develops with aging. Type-2 is commonly known where there is an imbalance between insulin levels and sensitivity, causing functional deficit of insulin[^1]. 

We are aiming to look at a predictive model for type-2 diabetes to predict diabetes risk, in order to enable persons to work with medical practitioners and carers to enable early intervention and assessment.  Strong international evidence shows diabetes prevention programs can assist in prevention of type-2 diabetes in up to 58% of cases [^4]. 

We are planning to in the future look at integration of Flash Glucose monitors or Blood Glucose Monitors to augment this to ensure better outcomes, as well as push requests and notifications from the device to advise people of reminders for insulin, food, exercise and medication.  This would also be augmented by questionnaires that could be set up from the dashboard to check in regularly.

## Definitions and Diagnosis for Diabetes

For this, we are looking at diabetes and looking to further analysis by using prediabetes as well for prediction.

As part of the work, we researched diabetes, symptoms, diagnosis thresholds in order to ascertain further technical understanding of the disease and how to assess data and datasets that we would use.

We also looked at finding data that had prediabetes, as being able to predict prior to diagnosis of diabetes could lead to better health outcomes, and potentially enable prevention or delay of developing diabetes.

Definitions and glossary of terms:
For further info, refer to the GLUCOSEMONITORINGRESEARCH.md file
- Blood Glucose Level (BGL) 
- Blood Glucose - level of glucose in your blood.
- HbA1c (also known as 'glycated heamoglobin).  Does not require fasting or prep; tests the amount of glycated haemoglobin.
- Fasting - inital blood glucose level taken, after not eating for 12 hours prior (generally)
- 2 hr glucose - blood glucose level taken at 2hrs after fasting, after having consumed a specificied glucose solution. 
- Random - Random time blood test.
- Oral glucose tolerance test - a test where a patient fasts for 
- Target Range - the specified BGL target range
- Time in Target - time BGL is in target range
- Finger prick - device to piece finger (lancet) to extract blood drop
- Flash Glucose - continuous blood glucose monitor that reads and transmits continuously
- Glucose monitor - can be used to take blood glucose from a finger prick and strip, singular reading per strip, not continuous
- Hypoglycaemia (also known as 'hypos') - BGL below 4mmol/L
- Hyperglycaemia - BGL above 15mmol/L

Diagnostic criteria for diabetes:
- Diagnostic criteria for Diabetes as per Australian Diabetes Society, 'Clinical Guidelines, HbA1c for Diagnosis of Diabetes Mellitus (May 2023)' [^5] is: 
    - 1. HbA1c ≥6.5% (48 mmol/mol) 
    - 2. Fasting glucose ≥7.0 mmol/L 
    - 3. Random glucose ≥11.1 mmol/L 
    - 4. On a 75 g oral glucose tolerance test: fasting glucose ≥7.0 mmol/L or 2 hr glucose ≥11.1 mmol/L 

- Diagnostic criteria for Pre-Diabetes in Australia as per Royal Australian College of General Practicioners (RACGP) [^6] is;  
    - Prediabetes: Diagnostic definitions of impaired fasting glucose (IFG) and impaired glucose tolerance (IGT)11 
    - The presence of prediabetes is defined according to the results of a two-hour oral glucose tolerance test (OGTT). 
 
- IFG: 
    - 1. fasting glucose 6.1–6.9 mmol/L, and 
    - 2. two-hour glucose <7.8 mmol/L 

- IGT: 
    - 1. fasting glucose <7 mmol/L, and 
    - 2. two-hour glucose ≥7.8 mmol/L and ≤11 mmol/L. 

Common Risk Assessment Tool:
- Below is the currently Australian Diabetes Risk Assessment Tool (AUDRISK) features that are used to assess the risk of developing diabetes in the next five years [^7], [^8]. This helps us look at potential features that may assist us.

    - 1. Age 
    - 2. Gender 
    - 3a. Descent 
    - 3b. Location of Birth 
    - 4. Family history of Diabetes 
    - 5. Previous high blood glucose 
    - 6. Medication for high blood pressure 
    - 7. Smoking 
    - 8. Vegetable intake 
    - 9. Exercise 
    - 10. Waist measurement 

- If you scored higher than 12 on the AUDRISK, you would be recommended to seek medical advice, and take a Blood Glucose test to assess if you have diabetes [^9].

- Of note; over the age of 65, Australian's should be screened for Diabetes every three years, if no other risk factors exist, in which case, it would be more frequently [^10]. 

Common symptoms of type-2 diabetes [^11], [^12]:
- Common symptoms can take a period of time, even years to develop.
    - 1. feeling very thirsty 
    - 2. needing to urinate more often than usual 
    - 3. blurred vision 
    - 4. feeling tired 
    - 5. losing weight unintentionally  

Common damage due to diabetes includes [^11], [^12]:
- Common damage due to diabetes can include, but is not limited to:
    - 1. Damage blood vessels in the heart, eyes, kidneys and nerves. 
    - 2. Higher risk of health problems including heart attack, stroke and kidney failure. 
    - 3. Permanent vision loss by damaging blood vessels in the eyes. 
    - 4. Nerve damage and poor blood flow, especially to extremities such as feet. This can cause foot ulcers and may lead to amputation. This can also lead to increased risks of falls, especially for the elderly. 

Background for recommendations pertaining to specific features, please refer to the following for the technical background from the US Department of Health and Human Services, Centre for Disease Control, Indicators for Chronic Disease Surveillance - United States, 2013 [^13]. 

Utilising this technical information as part of our analysis and modelling will assist in ensuring the integrity and feasibility of the analysis and further modelling.

## Data Analytics
To analyse this data, the following have been used:
- GPU Support and related
    - [NVIDIA CUDA](https://developer.nvidia.com/cuda-downloads)

To analyse this data, as well as to train machine learning classification models, a number of python libraries have been incorporated into the project:
- Data Analytics / Transformation:
    - [Pandas](https://pandas.pydata.org/docs/reference/index.html)
    - [Numpy](https://numpy.org/doc/stable/reference/index.html#reference)
- Visualization:
    - [MatPlotLib](https://matplotlib.org/stable/api/index.html)
    - [Seaborn](https://seaborn.pydata.org/api.html)
- Machine Learning:
    - [Pyclustering](https://pyclustering.github.io/docs/0.8.2/html/index.html)
    - [Pillow](https://pypi.org/project/pillow/)
    - [Scikit-Learn](https://scikit-learn.org/stable/api/index.html)
    - [Tensorflow](https://www.tensorflow.org/api_docs/python/tf) / [Keras](https://keras.io/api/)
    - [KerasTuner](https://keras.io/keras_tuner/#quick-introduction)

To utilise GPU from local destop; refer to the specific documention in each notebook. 

### Dataset used
A new dataset has been sourced and used for greater accuracy and integrity, as well as to ensure greater ability at prediction based on accurate features, as well as potential for further features for analysis.

Of note: The data for these datasets were sourced initially from the US Department of Health and Human Services, Centre for Disease Control (CDC).  The original dataset locations are:
    - [Behavioral Risk Factor Surveillance System](https://www.cdc.gov/brfss/annual_data/annual_data.htm)
    - [CDC - 2015 Behavioural Risk Factor Surveillance System (BRFSS) Survey Data and Documentation](https://www.cdc.gov/brfss/annual_data/annual_2015.html)
    - [The Behavioural Risk Factor Surveillance System 2015 Codebook](https://www.cdc.gov/brfss/annual_data/2015/pdf/codebook15_llcp.pdf)

The first dataset is: 
    - [CDC Diabetes Health Indicators](https://archive.ics.uci.edu/dataset/891/cdc+diabetes+health+indicators)
    - [CDC Diabetes Data](https://archive.ics.uci.edu/static/public/891/data.csv)
    - Data Abstract: The Diabetes Health Indicators Dataset contains healthcare statistics and lifestyle survey information about people in general along with their diagnosis of diabetes. The 35 features consist of some demographics, lab test results, and answers to survey questions for each patient. The target variable for classification is whether a patient has diabetes, is pre-diabetic, or healthy.

There are 253680 instances, and 20 features of data. 
For this dataset; 'Diabetes' (as positive) includes both diabetic and prediabetic people.

| Variable Name| Role| Type| Demographic| Description| Units| Missing Values|
| -| -| -| -| -| -| -|
| Diabetes_binary| Target| Binary| | 0 = no diabetes 1 = prediabetes or diabetes| | no|
| HighBP| Feature| Binary| | 0 = no high BP 1 = high BP| | no|
| HighChol| Feature| Binary| | 0 = no high cholesterol 1 = high cholesterol| | no|
| CholCheck| Feature| Binary| | 0 = no cholesterol check in 5 years 1 = yes cholesterol check in 5 years| | no|
| BMI| Feature| Integer| | Body Mass Index| | no|
| Smoker| Feature| Binary| | Have you smoked at least 100 cigarettes in your entire life? [Note: 5 packs = 100 cigarettes] 0 = no 1 = yes| | no|
| Stroke| Feature| Binary| | (Ever told) you had a stroke. 0 = no 1 = yes| | no|
| HeartDiseaseorAttack| Feature| Binary| | coronary heart disease (CHD) or myocardial infarction (MI) 0 = no 1 = yes| | no|
| PhysActivity| Feature| Binary| | physical activity in past 30 days - not including job 0 = no 1 = yes| | no|
| Fruits| Feature| Binary| | Consume Fruit 1 or more times per day 0 = no 1 = yes| | no|
| Veggies| Feature| Binary| | Consume Vegetables 1 or more times per day 0 = no 1 = yes| | no|
| HvyAlcoholConsump| Feature| Binary| | Heavy drinkers (adult men having more than 14 drinks per week and adult women having more than 7 drinks per week) 0 = no 1 = yes| | no|
| AnyHealthcare| Feature| Binary| | Have any kind of health care coverage, including health insurance, prepaid plans such as HMO, etc. 0 = no 1 = yes| | no|
| NoDocbcCost| Feature| Binary| | Was there a time in the past 12 months when you needed to see a doctor but could not because of cost? 0 = no 1 = yes| | no|
| GenHlth| Feature| Integer| | Would you say that in general your health is: scale 1-5 1 = excellent 2 = very good 3 = good 4 = fair 5 = poor| | no|
| MentHlth| Feature| Integer| | Now thinking about your mental health, which includes stress, depression, and problems with emotions, for how many days during the past 30 days was your mental health not good? scale 1-30 days| | no|
| PhysHlth| Feature| Integer| | Now thinking about your physical health, which includes physical illness and injury, for how many days during the past 30 days was your physical health not good? scale 1-30 days| | no|
| DiffWalk| Feature| Binary| | Do you have serious difficulty walking or climbing stairs? 0 = no 1 = yes| | no|
| Sex| Feature| Binary| Sex| 0 = female 1 = male| | no|
| Age| Feature| Integer| Age| 13-level age category (_AGEG5YR see codebook) 1 = 18-24 9 = 60-64 13 = 80 or older| | no|
| Education| Feature| Integer| Education Level| Education level (EDUCA see codebook) scale 1-6 1 = Never attended school or only kindergarten 2 = Grades 1 through 8 (Elementary) 3 = Grades 9 through 11 (Some high school) 4 = Grade 12 or GED (High school graduate) 5 = College 1 year to 3 years (Some college or technical school) 6 = College 4 years or more (College graduate)| | no|
| Income| Feature| Integer| Income| Income scale (INCOME2 see codebook) scale 1-8 1 = less than $10,000 5 = less than $35,000 8 = $75,000 or more| | no|


The second dataset folder contains three files, and is also based on the BRFSS 2015.  This is being used to extend analysis to look at prediabetes, as the files include where prediabetes and diabetes are listed as separate entries.  This is being used to further enhance analysis and modelling.
    - [Diabetes Health Indicators](https://www.kaggle.com/datasets/alexteboul/diabetes-health-indicators-dataset)
    - [Originally_referenced_CDC_dataset](https://www.cdc.gov/brfss/annual_data/annual_data.htm)
    - [Data_Referenced_through](https://www.kaggle.com/datasets/cdc/behavioral-risk-factor-surveillance-system)
    - Abstract: This dataset contains 3 files: 
            - diabetes _ 012 _ health _ indicators _ BRFSS2015.csv is a clean dataset of 253,680 survey responses to the CDC's BRFSS2015. The target variable Diabetes_012 has 3 classes. 0 is for no diabetes or only during pregnancy, 1 is for prediabetes, and 2 is for diabetes. There is class imbalance in this dataset. This dataset has 21 feature variables
            - diabetes _ binary _ 5050split _ health _ indicators _ BRFSS2015.csv is a clean dataset of 70,692 survey responses to the CDC's BRFSS2015. It has an equal 50-50 split of respondents with no diabetes and with either prediabetes or diabetes. The target variable Diabetes_binary has 2 classes. 0 is for no diabetes, and 1 is for prediabetes or diabetes. This dataset has 21 feature variables and is balanced.
            - diabetes _ binary _ health _ indicators _ BRFSS2015.csv is a clean dataset of 253,680 survey responses to the CDC's BRFSS2015. The target variable Diabetes_binary has 2 classes. 0 is for no diabetes, and 1 is for prediabetes or diabetes. This dataset has 21 feature variables and is not balanced.

The columns for all three are:

| Variable Name| Role| Type| Demographic| Description| Units| Missing Values|
| -| -| -| -| -| -| -|
| Diabetes_binary| Target| Binary| | 0 = no diabetes 1 = prediabetes 2 = diabetes| | no|
| HighBP| Feature| Binary| | 0 = no high BP 1 = high BP| | no|
| HighChol| Feature| Binary| | 0 = no high cholesterol 1 = high cholesterol| | no|
| CholCheck| Feature| Binary| | 0 = no cholesterol check in 5 years 1 = yes cholesterol check in 5 years| | no|
| BMI| Feature| Integer| | Body Mass Index| | no|
| Smoker| Feature| Binary| | Have you smoked at least 100 cigarettes in your entire life? [Note: 5 packs = 100 cigarettes] 0 = no 1 = yes| | no|
| Stroke| Feature| Binary| | (Ever told) you had a stroke. 0 = no 1 = yes| | no|
| HeartDiseaseorAttack| Feature| Binary| | coronary heart disease (CHD) or myocardial infarction (MI) 0 = no 1 = yes| | no|
| PhysActivity| Feature| Binary| | physical activity in past 30 days - not including job 0 = no 1 = yes| | no|
| Fruits| Feature| Binary| | Consume Fruit 1 or more times per day 0 = no 1 = yes| | no|
| Veggies| Feature| Binary| | Consume Vegetables 1 or more times per day 0 = no 1 = yes| | no|
| HvyAlcoholConsump| Feature| Binary| | Heavy drinkers (adult men having more than 14 drinks per week and adult women having more than 7 drinks per week) 0 = no 1 = yes| | no|
| AnyHealthcare| Feature| Binary| | Have any kind of health care coverage, including health insurance, prepaid plans such as HMO, etc. 0 = no 1 = yes| | no|
| NoDocbcCost| Feature| Binary| | Was there a time in the past 12 months when you needed to see a doctor but could not because of cost? 0 = no 1 = yes| | no|
| GenHlth| Feature| Integer| | Would you say that in general your health is: scale 1-5 1 = excellent 2 = very good 3 = good 4 = fair 5 = poor| | no|
| MentHlth| Feature| Integer| | Now thinking about your mental health, which includes stress, depression, and problems with emotions, for how many days during the past 30 days was your mental health not good? scale 1-30 days| | no|
| PhysHlth| Feature| Integer| | Now thinking about your physical health, which includes physical illness and injury, for how many days during the past 30 days was your physical health not good? scale 1-30 days| | no|
| DiffWalk| Feature| Binary| | Do you have serious difficulty walking or climbing stairs? 0 = no 1 = yes| | no|
| Sex| Feature| Binary| Sex| 0 = female 1 = male| | no|
| Age| Feature| Integer| Age| 13-level age category (_AGEG5YR see codebook) 1 = 18-24 9 = 60-64 13 = 80 or older| | no|
| Education| Feature| Integer| Education Level| Education level (EDUCA see codebook) scale 1-6 1 = Never attended school or only kindergarten 2 = Grades 1 through 8 (Elementary) 3 = Grades 9 through 11 (Some high school) 4 = Grade 12 or GED (High school graduate) 5 = College 1 year to 3 years (Some college or technical school) 6 = College 4 years or more (College graduate)| | no|
| Income| Feature| Integer| Income| Income scale (INCOME2 see codebook) scale 1-8 1 = less than $10,000 5 = less than $35,000 8 = $75,000 or more| | no|

Further details pertaining the breakdown of the breakdowns are available in the codebook.
- [The Behavioural Risk Factor Surveillance System 2015 Codebook](https://www.cdc.gov/brfss/annual_data/2015/pdf/codebook15_llcp.pdf)

### Previous datasets used
The previous datasets have been disgarded for the following reasons:

- [Dataset 1](https://www.kaggle.com/datasets/iammustafatz/diabetes-prediction-dataset)  
This Dataset was discarded for use, due to questions about the provenence of the data, accuracy, veractiy, as well as measures in the dataset.  

Concerns include the original poster refusing to provide provence of where the data is from [^14] when it was collected and how [^15] or what specific control and measure for Blood Glucose was taken, or what type of Blood Glucose it was (fasting, 2-hour, etc) [^16], which would be a requirement for assessing Diabetes from this measure, and specifies it 'appears to be random'.  As such this dataset is no longer being used.

- [Dataset 2](https://archive.ics.uci.edu/dataset/529/early+stage+diabetes+risk+prediction+dataset)

 was a very small sample of 520, from a questionaire in hospital.
Whilst good features, and has features that are symptoms of diabetes, it is a subset of people who have presented to a hospital, and is a small sample.  The features also are symptoms; so whilst they enable diagnosis, they do not enable lifestyle changes to assist the person, as they are already present.

## Approach
Techncial research into diabetes, symptoms, diagnosis, etc was understaken to gather a good understanding of the disease, and to enable accurate and informated analysis.
After the original datasets were analysed; they were discarded for use as noted above.

Further research into datasets was undertaken; and several were located that would be of use.  They are referenced above.

These have been analysed, and further analysis is being undertaken to ascertain a prediction model for diabetes, and hopefully prediabetes.




[^1]: (https://www.ncbi.nlm.nih.gov/books/NBK551501/)
[^2]: (https://www.diabetesaustralia.com.au/about-diabetes/diabetes-in-australia/)
[^3]: (https://www.aihw.gov.au/reports/diabetes/diabetes/contents/treatment-and-management/diabetes-hospitalisations)
[^4]: (https://www.diabetesaustralia.com.au/about-diabetes/myths-facts/
[^5]: (https://www.diabetessociety.com.au/guideline/)hba1c-for-diagnosis-of-diabetes-mellitus-may-2023/ 
[^6]: (https://www.racgp.org.au/clinical-resources/clinical-guidelines/key-racgp-guidelines/view-all-racgp-guidelines/national-guide/chapter-12-type-2-diabetes-prevention-and-early-de) 
[^7]: (https://www.health.gov.au/resources/apps-and-tools/the-australian-type-2-diabetes-risk-assessment-tool-ausdrisk/tool) 
[^8]: (https://www.health.gov.au/resources/apps-and-tools/the-australian-type-2-diabetes-risk-assessment-tool-ausdrisk) 
[^9]: (https://www.medicalert.org.au/articles/medicine-and-health-checks-for-every-age?gad_source=1&gclid=Cj0KCQjw28W2BhC7ARIsAPerrcIFBXFWorkWYRXqs_Nj6RQhnPV0PGN7eS1nmQnbaZ7sZECRlRSPr1caAqoQEALw_wcB) 
[^10]: (https://www.betterhealth.vic.gov.au/health/servicesandsupport/regular-health-checks)  
[^11]: (https://www.who.int/news-room/fact-sheets/detail/diabetes) 
[^12]: (https://www.healthdirect.gov.au/type-2-diabetes) 
[^13]: (https://www.cdc.gov/mmwr/preview/mmwrhtml/rr6401a1.htm)
[^14]: https://www.kaggle.com/datasets/iammustafatz/diabetes-prediction-dataset/discussion/406676#2282358
[^15]: https://www.kaggle.com/datasets/iammustafatz/diabetes-prediction-dataset/discussion/412933#2282361
[^16]: https://www.kaggle.com/datasets/iammustafatz/diabetes-prediction-dataset/discussion/405636#2282294