#include <testutilscxx.h>

void
assert_equals(CuTest *tc,
              const ChordLengths &cl1,
              const ChordLengths &cl2)
{
	// Spline
	assert_equal_shape(tc,
	                   cl1.spline(),
	                   cl2.spline());

	// Size
	CuAssertIntEquals(tc,
	                  (int) cl1.size(),
	                  (int) cl2.size());

	// Knots
	vector<real> knots1 = cl1.knots();
	vector<real> knots2 = cl2.knots();
	CuAssertIntEquals(tc,
	                  (int) knots1.size(),
	                  (int) knots2.size());
	for (size_t i = 0; i < cl1.size(); i++) {
		CuAssertDblEquals(tc,
		                  knots1[i],
		                  knots2[i],
		                  TS_KNOT_EPSILON);
	}

	// Values
	vector<real> lengths1 = cl1.lengths();
	vector<real> lengths2 = cl2.lengths();
	CuAssertIntEquals(tc,
	                  (int) lengths1.size(),
	                  (int) lengths2.size());
	for (size_t i = 0; i < lengths1.size(); i++) {
		CuAssertDblEquals(tc,
		                  lengths1[i],
		                  lengths2[i],
		                  POINT_EPSILON);
	}
}

void
chordlengths_copy_ctor(CuTest *tc)
{
	// Given
	BSpline spline(4, 2, 3);
	spline.setControlPoints({
			100, -100,
			200, -200,
			300, -300,
			400, -400
		});
	std::vector<real> knots = spline.uniformKnotSeq(100);
	ChordLengths lengths = spline.chordLengths(knots);

	// When
	ChordLengths copy(lengths);

	// Then
	assert_equals(tc, lengths, copy);
}

void
chordlengths_move_ctor(CuTest *tc)
{
	// Given
	BSpline spline(4, 2, 3);
	spline.setControlPoints({
			100, -100,
			200, -200,
			300, -300,
			400, -400
		});
	std::vector<real> knots = spline.uniformKnotSeq(100);
	ChordLengths lengths = spline.chordLengths(knots);
	ChordLengths toBeMoved(lengths);

	// When
	ChordLengths move(std::move(toBeMoved));

	// Then
	assert_equals(tc, lengths, move);
}

void
chordlengths_copy_assign(CuTest *tc)
{
	// Given
	BSpline spline(4, 2, 3);
	spline.setControlPoints({
			100, -100,
			200, -200,
			300, -300,
			400, -400
		});
	ChordLengths lengths = spline.chordLengths(spline.uniformKnotSeq(100));
	ChordLengths copy = spline.chordLengths(spline.uniformKnotSeq(50));
	CuAssertTrue(tc, lengths.size() != copy.size());

	// When
	copy = lengths;

	// Then
	assert_equals(tc, lengths, copy);
}

void
chordlengths_move_assign(CuTest *tc)
{
	// Given
	BSpline spline(4, 2, 3);
	spline.setControlPoints({
			100, -100,
			200, -200,
			300, -300,
			400, -400
		});
	ChordLengths lengths = spline.chordLengths(spline.uniformKnotSeq(100));
	ChordLengths toBeMoved(lengths);
	ChordLengths move = spline.chordLengths(spline.uniformKnotSeq(50));
	CuAssertTrue(tc, lengths.size() != move.size());

	// When
	move = std::move(toBeMoved);

	// Then
	assert_equals(tc, lengths, move);
}

void
chordlengths_default_ctor(CuTest *tc)
{
	// Given
	BSpline spline;
	std::vector<real> knots;
	ChordLengths empty = spline.chordLengths(knots);

	// When
	ChordLengths *defaultCtor = new ChordLengths();

	// Then
	assert_equals(tc, empty, *defaultCtor);
	delete defaultCtor;
}

void
chordlengths_empty_map(CuTest *tc)
{
	// Given
	BSpline spline;
	ChordLengths empty = spline.chordLengths({});

	// When/Then
	try {
		empty.tToKnot((real) 0.0);
		CuFail(tc, "expected exception");
	} catch(std::exception) {}
}

void
chordlengths_default_map(CuTest *tc)
{
	// Given
	ChordLengths *defaultCtor = new ChordLengths();

	// When/Then
	try {
		defaultCtor->tToKnot((real) 0.0);
		CuFail(tc, "expected exception");
	} catch(std::exception) {}
	delete defaultCtor;
}

void
chordlengths_equidistantKnotSeq(CuTest *tc)
{
	// Given
	BSpline spline = BSpline(4);
	spline.setControlPoints({
			100, 100,
			200, 130,
			300, -50,
			400, 0});

	// When
	std::vector<real> knotsExp = spline.equidistantKnotSeq(100, 200);
	std::vector<real> knotsAct = spline.chordLengths(200)
	                                   .equidistantKnotSeq(100);

	// Then
	CuAssertIntEquals(tc, knotsExp.size(), knotsAct.size());
	for (int i = 0; i < knotsExp.size(); i++) {
		double dist = (double) ts_distance(&knotsExp[i],
		                                   &knotsAct[i],
		                                   1);
		CuAssertDblEquals(tc, 0.0, dist, TS_POINT_EPSILON);
	}
}

CuSuite *
get_chordlengths_suite()
{
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, chordlengths_copy_ctor);
	SUITE_ADD_TEST(suite, chordlengths_move_ctor);
	SUITE_ADD_TEST(suite, chordlengths_copy_assign);
	SUITE_ADD_TEST(suite, chordlengths_move_assign);
	SUITE_ADD_TEST(suite, chordlengths_default_ctor);
	SUITE_ADD_TEST(suite, chordlengths_empty_map);
	SUITE_ADD_TEST(suite, chordlengths_default_map);
	SUITE_ADD_TEST(suite, chordlengths_equidistantKnotSeq);
	return suite;
}
