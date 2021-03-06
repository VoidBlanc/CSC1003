#include <stdio.h>
#include "nbprob.h"

// =============================================================================
// Prior Probability
// =============================================================================
void *priorprobcalc(Features *dataset, struct FeatureSet *probresult, unsigned int rowcount)
{
    //struct FeatureSet *probresult;
    unsigned int normcount = 0; // normal count
    unsigned int altcount = 0;  // altered count
    // Calculate  the number of normal / altered
    for (int i = 0; i < rowcount; i++)
    {
        normcount = dataset[i].semen_diag == NORMAL_YES ? normcount + 1 : normcount;
        altcount = dataset[i].semen_diag == ALTERED_NO ? altcount + 1 : altcount;
    }

    // calculate P(normal) & P(altered)
    probresult->prob_normal = (double)normcount / rowcount;
    probresult->prob_altered = (double)altcount / rowcount;
    probresult->normal_count = normcount;
    probresult->altered_count = altcount;
    return 0;
}

// =============================================================================
// Conditional Probability
// =============================================================================

void *cpcalc(Features *dataset, struct FeatureSet *priorprob, Probability *resultset, unsigned int rowcount)
{
    resultset->semen_diagnosis = *priorprob; // Store Prior prob (Based on Normal / Altered SEMEN DIAGNOSIS)
    int normcount = 0;                       // Number of Normal
    int altcount = 0;                        // Number of Altered
    Features tempfeature = {0};              // Initialize & to hold features from dataset
    // ==========================================================================================
    // normcount : Number of Normal semen diagnosis  altcount : Number of Altered sement dagnosis
    // ==========================================================================================
    normcount = resultset->semen_diagnosis.normal_count; // Get the normal_count into the normcount
    altcount = resultset->semen_diagnosis.altered_count; // Get the altered_count into the altcount
    for (int i = 0; i < rowcount; i++)
    {
        tempfeature = (*(dataset + i)); // Pointer to get the data at index i
        if (tempfeature.semen_diag == NORMAL_YES)
        {
            // Seasons
            if (tempfeature.seasons == WINTER)
            {
                resultset->winter.normal_count += 1;
            }
            else if (tempfeature.seasons == (float)SPRING)
            {
                resultset->spring.normal_count += 1;
            }
            else if (tempfeature.seasons == (float)SUMMER)
            {
                resultset->summer.normal_count += 1;
            }
            else if (tempfeature.seasons == (float)FALL)
            {
                resultset->fall.normal_count += 1;
            }
            // ==============================
            // Childish Disease
            if (tempfeature.childish_disease == NORMAL_YES)
            {
                resultset->cdisease_yes.normal_count += 1;
            }
            else
            {
                resultset->cdisease_no.normal_count += 1;
            }
            // ==============================
            // Accident / Serious Trauma
            if (tempfeature.trauma == NORMAL_YES)
            {
                resultset->trauma_yes.normal_count += 1;
            }
            else
            {
                resultset->trauma_no.normal_count += 1;
            }
            // ==============================
            // Surgical Intervention
            if (tempfeature.surgical == NORMAL_YES)
            {
                resultset->surgical_yes.normal_count += 1;
            }
            else
            {
                resultset->surgical_no.normal_count += 1;
            }
            // ==============================
            // High Fever
            if (tempfeature.high_fever == HIGH_FEVER_LESSTHAN)
            {
                resultset->highfever_lttm.normal_count += 1;
            }
            else if (tempfeature.high_fever == HIGH_FEVER_MORETHAN)
            {
                resultset->highfever_mttm.normal_count += 1;
            }
            else if (tempfeature.high_fever == HIGH_FEVER_NO)
            {
                resultset->highfever_none.normal_count += 1;
            }
            // ==============================
            // Frequency of Alcohol Consumption
            if (tempfeature.alc_consumpfreq == SERVERAL_A_DAY)
            {
                resultset->freqalch_std.normal_count += 1;
            }
            else if (tempfeature.alc_consumpfreq == EVERY_DAY)
            {
                resultset->freqalch_every.normal_count += 1;
            }
            else if (tempfeature.alc_consumpfreq == SERVERAL_A_WEEK)
            {
                resultset->freqalch_stw.normal_count += 1;
            }
            else if (tempfeature.alc_consumpfreq == ONCE_A_WEEK)
            {
                resultset->freqalch_oaw.normal_count += 1;
            }
            else if (tempfeature.alc_consumpfreq == HARDLY_NEVER)
            {
                resultset->freqalch_hardly.normal_count += 1;
            }

            // ==============================
            // Smoking Habit
            if (tempfeature.smoking_habit == SH_NEVER)
            {
                resultset->smokehabit_never.normal_count += 1;
            }
            else if (tempfeature.smoking_habit == SH_OCCASIONALLY)
            {
                resultset->smokehabit_occ.normal_count += 1;
            }
            else if (tempfeature.smoking_habit == SH_DAILY)
            {
                resultset->smokehabit_daily.normal_count += 1;
            }

            // ==============================

            // Age of Analysis & Number of hours sitting per table
            resultset->ageanalysis.sum_normal += tempfeature.ageanalysis;
            resultset->ageanalysis.normal_count += 1;
            resultset->sitting_hours.sum_normal += tempfeature.sitting_duration;
            resultset->sitting_hours.normal_count += 1;
        }
        else
        {
            // Season
            if (tempfeature.seasons == WINTER)
            {
                resultset->winter.altered_count += 1;
            }
            else if (tempfeature.seasons == (float)SPRING)
            {
                resultset->spring.altered_count += 1;
            }
            else if (tempfeature.seasons == (float)SUMMER)
            {
                resultset->summer.altered_count += 1;
            }
            else if (tempfeature.seasons == (float)FALL)
            {
                resultset->fall.altered_count += 1;
            }
            // ==============================
            // Childish Disease
            if (tempfeature.childish_disease == NORMAL_YES)
            {
                resultset->cdisease_yes.altered_count += 1;
            }
            else
            {
                resultset->cdisease_no.altered_count += 1;
            }
            // ==============================
            // Accident / Serious Trauma
            if (tempfeature.trauma == NORMAL_YES)
            {
                resultset->trauma_yes.altered_count += 1;
            }
            else
            {
                resultset->trauma_no.altered_count += 1;
            }
            // ==============================
            // Surgical Intervention
            if (tempfeature.surgical == NORMAL_YES)
            {
                resultset->surgical_yes.altered_count += 1;
            }
            else
            {
                resultset->surgical_no.altered_count += 1;
            }
            // ==============================
            // High Fever
            if (tempfeature.high_fever == HIGH_FEVER_LESSTHAN)
            {
                resultset->highfever_lttm.altered_count += 1;
            }
            else if (tempfeature.high_fever == HIGH_FEVER_MORETHAN)
            {
                resultset->highfever_mttm.altered_count += 1;
            }
            else if (tempfeature.high_fever == HIGH_FEVER_NO)
            {

                resultset->highfever_none.altered_count += 1;
            }
            // ==============================

            // Frequency of Alcohol Consumption
            if (tempfeature.alc_consumpfreq == SERVERAL_A_DAY)
            {
                resultset->freqalch_std.altered_count += 1;
            }
            else if (tempfeature.alc_consumpfreq == (float)EVERY_DAY)
            {
                resultset->freqalch_every.altered_count += 1;
            }
            else if (tempfeature.alc_consumpfreq == (float)SERVERAL_A_WEEK)
            {
                resultset->freqalch_stw.altered_count += 1;
            }
            else if (tempfeature.alc_consumpfreq == (float)ONCE_A_WEEK)
            {
                resultset->freqalch_oaw.altered_count += 1;
            }
            else if (tempfeature.alc_consumpfreq == HARDLY_NEVER)
            {
                resultset->freqalch_hardly.altered_count += 1;
            }

            // ==============================
            // Smoking Habit
            if (tempfeature.smoking_habit == SH_NEVER)
            {

                resultset->smokehabit_never.altered_count += 1;
            }
            else if (tempfeature.smoking_habit == SH_OCCASIONALLY)
            {
                resultset->smokehabit_occ.altered_count += 1;
            }
            else if (tempfeature.smoking_habit == SH_DAILY)
            {
                resultset->smokehabit_daily.altered_count += 1;
            }
            // ==============================

            // Age of Analysis & Number of hours sitting per table
            resultset->ageanalysis.sum_altered += tempfeature.ageanalysis;
            resultset->ageanalysis.altered_count += 1;

            resultset->sitting_hours.sum_altered += tempfeature.sitting_duration;
            resultset->sitting_hours.altered_count += 1;
        }
    }

    // ==============================
    // Probability - Normal
    // ==============================
    //
    resultset->winter.prob_normal = (double)(resultset->winter.normal_count + ALPHA) / ((normcount + (4 * ALPHA)));
    resultset->spring.prob_normal = (double)(resultset->spring.normal_count + ALPHA) / (normcount + (4 * ALPHA));
    resultset->summer.prob_normal = (double)(resultset->summer.normal_count + ALPHA) / (normcount + (4 * ALPHA));
    resultset->fall.prob_normal = (double)(resultset->fall.normal_count + ALPHA) / (normcount + (4 * ALPHA));
    resultset->cdisease_yes.prob_normal = (double)(resultset->cdisease_yes.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->cdisease_no.prob_normal = (double)(resultset->cdisease_no.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->trauma_yes.prob_normal = (double)(resultset->trauma_yes.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->trauma_no.prob_normal = (double)(resultset->trauma_no.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->surgical_yes.prob_normal = (double)(resultset->surgical_yes.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->surgical_no.prob_normal = (double)(resultset->surgical_no.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    //
    resultset->highfever_lttm.prob_normal = (double)(resultset->highfever_lttm.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->highfever_mttm.prob_normal = (double)(resultset->highfever_mttm.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->highfever_none.prob_normal = (double)(resultset->highfever_none.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    //
    resultset->freqalch_std.prob_normal = (double)(resultset->freqalch_std.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalch_every.prob_normal = (double)(resultset->freqalch_every.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalch_stw.prob_normal = (double)(resultset->freqalch_stw.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalch_oaw.prob_normal = (double)(resultset->freqalch_oaw.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalch_hardly.prob_normal = (double)(resultset->freqalch_hardly.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    //
    resultset->smokehabit_never.prob_normal = (double)(resultset->smokehabit_never.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->smokehabit_occ.prob_normal = (double)(resultset->smokehabit_occ.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->smokehabit_daily.prob_normal = (double)(resultset->smokehabit_daily.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->ageanalysis.mean_normal = (double)(resultset->ageanalysis.sum_normal) / (normcount);
    resultset->sitting_hours.mean_normal = (double)(resultset->sitting_hours.sum_normal) / (normcount);

    // ==============================
    // Probability - Altered
    // ==============================

    resultset->winter.prob_altered = (double)(resultset->winter.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->spring.prob_altered = (double)(resultset->spring.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->summer.prob_altered = (double)(resultset->summer.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->fall.prob_altered = (double)(resultset->fall.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->cdisease_yes.prob_altered = (double)(resultset->cdisease_yes.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->cdisease_no.prob_altered = (double)(resultset->cdisease_no.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->trauma_yes.prob_altered = (double)(resultset->trauma_yes.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->trauma_no.prob_altered = (double)(resultset->trauma_no.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->surgical_yes.prob_altered = (double)(resultset->surgical_yes.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->surgical_no.prob_altered = (double)(resultset->surgical_no.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->highfever_lttm.prob_altered = (double)(resultset->highfever_lttm.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->highfever_mttm.prob_altered = (double)(resultset->highfever_mttm.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->highfever_none.prob_altered = (double)(resultset->highfever_none.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->freqalch_std.prob_altered = (double)(resultset->freqalch_std.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalch_every.prob_altered = (double)(resultset->freqalch_every.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalch_stw.prob_altered = (double)(resultset->freqalch_stw.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalch_oaw.prob_altered = (double)(resultset->freqalch_oaw.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalch_hardly.prob_altered = (double)(resultset->freqalch_hardly.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->smokehabit_never.prob_altered = (double)(resultset->smokehabit_never.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->smokehabit_occ.prob_altered = (double)(resultset->smokehabit_occ.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->smokehabit_daily.prob_altered = (double)(resultset->smokehabit_daily.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->ageanalysis.mean_altered = (double)(resultset->ageanalysis.sum_altered) / (altcount);
    resultset->sitting_hours.mean_altered = (double)(resultset->sitting_hours.sum_altered) / (altcount);

    // Below is to calculate the variance altered and variance normal 
    // for age of analysis & num hrs sitting per table
    for (int j = 0; j < rowcount; j++)
    {
        tempfeature = (*(dataset + j));
        if (tempfeature.semen_diag == NORMAL_YES)
        {
            resultset->ageanalysis.var_normal += pow((tempfeature.ageanalysis - (resultset->ageanalysis.mean_normal)), 2);
            resultset->sitting_hours.var_normal += pow((tempfeature.sitting_duration - (resultset->sitting_hours.mean_normal)), 2);
        }
        else if (tempfeature.semen_diag == ALTERED_NO)
        {
            resultset->ageanalysis.var_altered += pow((tempfeature.ageanalysis - (resultset->ageanalysis.mean_altered)), 2);
            resultset->sitting_hours.var_altered += pow((tempfeature.sitting_duration - (resultset->sitting_hours.mean_altered)), 2);
        }
    }
    resultset->ageanalysis.var_normal /= (double)(normcount - 1);
    resultset->sitting_hours.var_normal /= (double)(normcount - 1);
    resultset->ageanalysis.var_altered /= (double)(altcount - 1);
    resultset->sitting_hours.var_altered /= (double)(altcount - 1);
    return 0;
}

// =============================================================================
// Posterior Probability
// =============================================================================
void *postprobcalc(Features *dataset, struct FeatureSet *fsetdatas, Probability *probdataset, Probability_Err *resultset, unsigned int rowcount)
{
    Probability probdatas = *probdataset;
    double tempprob_normal = 0, tempprob_altered = 0, tempprobnorm = 0;
    double tempgauss_age = 0, tempgauss_hrs = 0;
    int i = 0;
    for (i = 0; i < rowcount; i++)
    {
        tempprob_normal = 1;
        tempprob_altered = 1;

        // Seasons
        if (dataset[i].seasons == WINTER)
        {
            tempprob_normal *= probdatas.winter.prob_normal;
            tempprob_altered *= probdatas.winter.prob_altered;
        }
        else if (dataset[i].seasons == (float)SPRING)
        {
            tempprob_normal *= probdatas.spring.prob_normal;
            tempprob_altered *= probdatas.spring.prob_altered;
        }
        else if (dataset[i].seasons == (float)SUMMER)
        {
            tempprob_normal *= probdatas.summer.prob_normal;
            tempprob_altered *= probdatas.summer.prob_altered;
        }
        else if (dataset[i].seasons == (float)FALL)
        {
            tempprob_normal *= probdatas.fall.prob_normal;
            tempprob_altered *= probdatas.fall.prob_altered;
        }
        // ==============================
        // Childish DIsease
        if (dataset[i].childish_disease == NORMAL_YES)
        {
            tempprob_normal *= probdatas.cdisease_yes.prob_normal;
            tempprob_altered *= probdatas.cdisease_yes.prob_altered;
        }
        else
        {
            tempprob_normal *= probdatas.cdisease_no.prob_normal;
            tempprob_altered *= probdatas.cdisease_no.prob_altered;
        }
        // ==============================
        // Accident / Serious Trauma
        if (dataset[i].trauma == NORMAL_YES)
        {
            tempprob_normal *= probdatas.trauma_yes.prob_normal;
            tempprob_altered *= probdatas.trauma_yes.prob_altered;
        }
        else
        {
            tempprob_normal *= probdatas.trauma_no.prob_normal;
            tempprob_altered *= probdatas.trauma_no.prob_altered;
        }
        // ==============================
        // Surgical Intervention
        if (dataset[i].surgical == NORMAL_YES)
        {
            tempprob_normal *= probdatas.surgical_yes.prob_normal;
            tempprob_altered *= probdatas.surgical_yes.prob_altered;
        }
        else
        {
            tempprob_normal *= probdatas.surgical_no.prob_normal;
            tempprob_altered *= probdatas.surgical_no.prob_altered;
        }

        // ==============================
        // High fever
        if (dataset[i].high_fever == HIGH_FEVER_LESSTHAN)
        {
            tempprob_normal *= probdatas.highfever_lttm.prob_normal;
            tempprob_altered *= probdatas.highfever_lttm.prob_altered;
        }
        else if (dataset[i].high_fever == HIGH_FEVER_MORETHAN)
        {
            tempprob_normal *= probdatas.highfever_mttm.prob_normal;
            tempprob_altered *= probdatas.highfever_mttm.prob_altered;
        }
        else if (dataset[i].high_fever == HIGH_FEVER_NO)
        {
            tempprob_normal *= probdatas.highfever_none.prob_normal;
            tempprob_altered *= probdatas.highfever_none.prob_altered;
        }

        // ==============================
        // Frequency of Alcohol Consumption
        if (dataset[i].alc_consumpfreq == (float)SERVERAL_A_DAY)
        {
            tempprob_normal *= probdatas.freqalch_std.prob_normal;
            tempprob_altered *= probdatas.freqalch_std.prob_altered;
        }
        else if (dataset[i].alc_consumpfreq == (float)EVERY_DAY)
        {
            tempprob_normal *= probdatas.freqalch_every.prob_normal;
            tempprob_altered *= probdatas.freqalch_every.prob_altered;
        }
        else if (dataset[i].alc_consumpfreq == (float)SERVERAL_A_WEEK)
        {
            tempprob_normal *= probdatas.freqalch_stw.prob_normal;
            tempprob_altered *= probdatas.freqalch_stw.prob_altered;
        }
        else if (dataset[i].alc_consumpfreq == ONCE_A_WEEK)
        {
            tempprob_normal *= probdatas.freqalch_oaw.prob_normal;
            tempprob_altered *= probdatas.freqalch_oaw.prob_altered;
        }
        else if (dataset[i].alc_consumpfreq == HARDLY_NEVER)
        {
            tempprob_normal *= probdatas.freqalch_hardly.prob_normal;
            tempprob_altered *= probdatas.freqalch_hardly.prob_altered;
        }

        // ==============================
        // Smoking Habit
        if (dataset[i].smoking_habit == SH_NEVER)
        {
            tempprob_normal *= probdatas.smokehabit_never.prob_normal;
            tempprob_altered *= probdatas.smokehabit_never.prob_altered;
        }
        else if (dataset[i].smoking_habit == SH_OCCASIONALLY)
        {
            tempprob_normal *= probdatas.smokehabit_occ.prob_normal;
            tempprob_altered *= probdatas.smokehabit_occ.prob_altered;
        }
        else if (dataset[i].smoking_habit == SH_DAILY)
        {
            tempprob_normal *= probdatas.smokehabit_daily.prob_normal;
            tempprob_altered *= probdatas.smokehabit_daily.prob_altered;
        }

        // ==============================

        // Gaussian for age of analysis and num hrs sitting per table

        tempgauss_age = gaussiancalc(probdatas.ageanalysis.mean_normal, probdatas.ageanalysis.var_normal, dataset[i].ageanalysis);
        tempprob_normal *= tempgauss_age;
        tempgauss_hrs = gaussiancalc(probdatas.sitting_hours.mean_normal, probdatas.sitting_hours.var_normal, dataset[i].sitting_duration);
        tempprob_normal *= tempgauss_hrs;

        tempgauss_age = gaussiancalc(probdatas.ageanalysis.mean_altered, probdatas.ageanalysis.var_altered, dataset[i].ageanalysis);
        tempprob_altered *= tempgauss_age;
        tempgauss_hrs = gaussiancalc(probdatas.sitting_hours.mean_altered, probdatas.sitting_hours.var_altered, dataset[i].sitting_duration);
        tempprob_altered *= tempgauss_hrs;
        resultset[i].actual_nora = dataset[i].semen_diag;
        tempprob_normal = (tempprob_normal * fsetdatas->prob_normal) / (tempprob_altered + tempprob_normal);
        tempprob_altered = (tempprob_altered * fsetdatas->prob_altered) / (tempprob_altered + tempprob_normal);
        if (tempprob_normal >= tempprob_altered)
        {
            resultset[i].predicted_nora = 0;
        }
        else
        {
            resultset[i].predicted_nora = 1;
        }

        resultset[i].prob_normal = tempprob_normal;
        resultset[i].prob_altered = tempprob_altered;
    }
    return 0;
}

// =============================================================================
// Error Probability / Confusion Matrix :
// =============================================================================
void *cmatrix(Probability_Err *postprobdata, struct Confusion_Matrix *resultset, unsigned int rowcount, unsigned int index)
{
    int i;
    (*(resultset + index)).data_count = rowcount;
    (*(resultset + index)).true_pos = 0;
    (*(resultset + index)).true_neg = 0;
    (*(resultset + index)).false_pos = 0;
    (*(resultset + index)).false_neg = 0;
    (*(resultset + index)).prob_error = 0;

    for (i = 0; i < rowcount; i++)
    {
        if ((*(postprobdata + i)).actual_nora == (*(postprobdata + i)).predicted_nora)
        {
            if ((*(postprobdata + i)).actual_nora == 1 && (*(postprobdata + i)).predicted_nora == 1)
            {
                // No of times predict correctly that a patient is not normal
                (*(resultset + index)).true_pos += 1;
            }
            else if ((*(postprobdata + i)).actual_nora == 0 && (*(postprobdata + i)).predicted_nora == 0)
            {
                // No of times predict correctly that a patient is normal
                (*(resultset + index)).true_neg += 1;
            }
        }
        else
        {
            if ((*(postprobdata + i)).actual_nora == 0 && (*(postprobdata + i)).predicted_nora == 1)
            {
                // No of times predict wrongly that patient is not normal but patient is actually normal
                (*(resultset + index)).false_pos += 1;
            }

            if ((*(postprobdata + i)).actual_nora == 1 && (*(postprobdata + i)).predicted_nora == 0)
            {
                // No of times predict wrongly that patient is normal but patient is actually not normal
                (*(resultset + index)).false_neg += 1;
            }
            (*(resultset + index)).prob_error += 1;
        }
    }
    (*(resultset + index)).prob_error /= (float)rowcount;
    return 0;
}

// =============================================================================
// Gaussian Formula
// =============================================================================
double gaussiancalc(double mean, double variance, double xval)
{
    double result = 0;
    double zscore = (xval - mean);
    result = (1 / sqrt(2 * PI)) * exp(-1 * (pow(zscore, 2) / (2 * variance)));
    return result;
}

// =============================================================================
// GNUPLOT Graph Plotting
// =============================================================================
void plot_graph(Confusion_Matrix_Type *cmatrixdata, int n)
{

    FILE *p = popen("gnuplot -persist", "w");
    fprintf(p, "set title 'Chart for Probability of Error' \n");    // Set title for GNUPLOT
    fprintf(p, "set term qt font 'Arial,12' \n");                   // Set font for gnu plot
    fprintf(p, "set xlabel 'Training Data Size' \n");               // Set X-axis Label
    fprintf(p, "set ylabel 'Probability of Error %%' \n");          // Set Y-axis Label
    fprintf(p, "set style line 1 lc rgb 'blue' lt 1 lw 2 pt 7 \n"); // Line Style for training Data lt: LineTypes lw: LineWidth LC: LineCOlor
    fprintf(p, "set style line 2 lc rgb 'red' lt 1 lw 2 pt 6 \n");  // Set Y-axis Label

    int xval = 0;
    double yval = 0;
    if (p != NULL)
    {
        // Line Plot for Training Data
        fprintf(p, "$TRGDATA << EOD\n");
        for (int i = 0; i < n; i++)
        {
            xval = cmatrixdata->trg_cmatrix[i].data_count;       // X axis
            yval = cmatrixdata->trg_cmatrix[i].prob_error * 100; // Y axis in percentage
            fprintf(p, "%d %g\n", xval, yval);
        }
        fprintf(p, "EOD\n");

        // Line Plot for Test Data
        fprintf(p, "$TSTDATA << EOD\n");
        for (int k = n - 1; k >= 0; k--)
        {
            xval = cmatrixdata->trg_cmatrix[k].data_count;       //For Test Data use Traning data count to put them under same x axis
            yval = cmatrixdata->tst_cmatrix[k].prob_error * 100; // Y axis in percentage
            // If Test Data
            fprintf(p, "%d %g\n", xval, yval);
        }
        fprintf(p, "EOD\n");
    }
    // To plot the graph with data from the above lp : LinePoint ls: LineStyle
    fprintf(p, "plot '$TRGDATA' with lp title 'Training Data' ls 1, '$TSTDATA' with lp title 'Test Data' ls 2\n");
    fflush(p);
    pclose(p);
}
// =============================================================================
// Confusion Matrix Printout
// =============================================================================
void printmatrix(Confusion_Matrix_Type *cmatrixdata, int n)
{

    for (int i = 0; i < n; i++)
    {
        printf("\n==========================================================================");
        printf("\n||                          TRAINING DATA                               ||");
        printf("\n||                                %d                                    ||", cmatrixdata->trg_cmatrix[i].data_count);
        printf("\n==========================================================================");
        printf("\n                      ||    PREDICTED POSITIVE        PREDICTED NEGATIVE  ");
        printf("\n----------------------||--------------------------------------------------");
        printf("\n    ACTUAL POSITIVE   ||           TP : %d                FN : %d           ", cmatrixdata->trg_cmatrix[i].true_pos, cmatrixdata->trg_cmatrix[i].false_neg);
        printf("\n----------------------||--------------------------------------------------");
        printf("\n    ACTUAL NEGATIVE   ||           FP : %d                TN : %d          ", cmatrixdata->trg_cmatrix[i].false_pos, cmatrixdata->trg_cmatrix[i].true_neg);
        printf("\n==========================================================================");
        printf("\n  Error of Probability  :   %lf", cmatrixdata->trg_cmatrix[i].prob_error);
        printf("\n==========================================================================\n");
        printf("\n==========================================================================");
        printf("\n||                            TEST DATA                                 ||");
        printf("\n||                                %d                                    ||", cmatrixdata->tst_cmatrix[i].data_count);
        printf("\n==========================================================================");
        printf("\n                     ||    PREDICTED POSITIVE        PREDICTED NEGATIVE  ");
        printf("\n---------------------||---------------------------------------------------");
        printf("\n    ACTUAL POSITIVE  ||           TP : %d                FN : %d           ", cmatrixdata->tst_cmatrix[i].true_pos, cmatrixdata->tst_cmatrix[i].false_neg);
        printf("\n---------------------||---------------------------------------------------");
        printf("\n    ACTUAL NEGATIVE  ||           FP : %d                TN : %d          ", cmatrixdata->tst_cmatrix[i].false_pos, cmatrixdata->tst_cmatrix[i].true_neg);
        printf("\n==========================================================================");
        printf("\n  Error of Probability  :   %lf", cmatrixdata->tst_cmatrix[i].prob_error);
        printf("\n==========================================================================\n");
    }
}