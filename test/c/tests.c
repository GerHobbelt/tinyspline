#include <testutils.h>

CuSuite* get_arr_fill_suite(void);
CuSuite* get_free_suite(void);
CuSuite* get_new_suite(void);
CuSuite* get_move_suite(void);
CuSuite* get_eval_suite(void);
CuSuite* get_set_knots_suite(void);
CuSuite* get_insert_knot_suite(void);
CuSuite* get_sample_suite(void);
CuSuite* get_to_beziers_suite(void);
CuSuite* get_interpolation_suite(void);
CuSuite* get_derive_suite(void);
CuSuite* get_bisect_suite(void);
CuSuite* get_save_load_suite(void);
CuSuite* get_elevate_degree_suite(void);
CuSuite* get_align_suite(void);
CuSuite* get_tension_suite(void);
CuSuite* get_morph_suite(void);
CuSuite* get_rmf_suite(void);
CuSuite* get_vector_suite(void);
CuSuite* get_chord_lengths_suite(void);
CuSuite* get_copy_suite(void);
CuSuite* get_sub_spline_suite(void);

int main(void)
{
	int fails;
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, get_arr_fill_suite());
	CuSuiteAddSuite(suite, get_free_suite());
	CuSuiteAddSuite(suite, get_new_suite());
	CuSuiteAddSuite(suite, get_move_suite());
	CuSuiteAddSuite(suite, get_eval_suite());
	CuSuiteAddSuite(suite, get_set_knots_suite());
	CuSuiteAddSuite(suite, get_insert_knot_suite());
	CuSuiteAddSuite(suite, get_sample_suite());
	CuSuiteAddSuite(suite, get_to_beziers_suite());
	CuSuiteAddSuite(suite, get_interpolation_suite());
	CuSuiteAddSuite(suite, get_derive_suite());
	CuSuiteAddSuite(suite, get_bisect_suite());
	CuSuiteAddSuite(suite, get_save_load_suite());
	CuSuiteAddSuite(suite, get_elevate_degree_suite());
	CuSuiteAddSuite(suite, get_align_suite());
	CuSuiteAddSuite(suite, get_tension_suite());
	CuSuiteAddSuite(suite, get_morph_suite());
	CuSuiteAddSuite(suite, get_rmf_suite());
	CuSuiteAddSuite(suite, get_vector_suite());
	CuSuiteAddSuite(suite, get_chord_lengths_suite());
	CuSuiteAddSuite(suite, get_copy_suite());
	CuSuiteAddSuite(suite, get_sub_spline_suite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("C Library:\n%s\n", output->buffer);
	fails = suite->failCount;

	CuStringDelete(output);
	CuSuiteDelete(suite);

	return fails? EXIT_FAILURE : EXIT_SUCCESS;
}
