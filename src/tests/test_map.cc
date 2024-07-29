#include <gtest/gtest.h>

#include <list>
#include <string>

#include "../s21_containers.h"

TEST(test_map, constructor_1) {
  s21::map<int, int> opa;

  EXPECT_TRUE(opa.empty());
  EXPECT_TRUE(opa.begin() == opa.end());
  ASSERT_EQ(opa.size(), 0);
}

TEST(test_map, constructor_2) {
  s21::map<int, int> opa;
  s21::map<int, int> aboba(opa);

  EXPECT_TRUE(opa.empty());
  EXPECT_TRUE(opa.begin() == opa.end());
  ASSERT_EQ(opa.size(), 0);

  EXPECT_TRUE(aboba.empty());
  EXPECT_TRUE(aboba.begin() == aboba.end());
  ASSERT_EQ(aboba.size(), 0);
}

TEST(test_map, constructor_3) {
  s21::map<int, int> opa{{1, 1}, {2, 2}, {3, 6}};
  s21::map<int, int> aboba(opa);

  EXPECT_FALSE(opa.empty());
  ASSERT_EQ(opa.size(), 3);

  auto it = opa.begin();

  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, 1);

  ++it;

  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, 2);
  ++it;

  ASSERT_EQ(it->first, 3);
  ASSERT_EQ(it->second, 6);

  ++it;

  ASSERT_EQ(it, opa.end());

  EXPECT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 3);

  it = aboba.begin();

  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, 1);

  ++it;

  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, 2);

  ++it;

  ASSERT_EQ(it->first, 3);
  ASSERT_EQ(it->second, 6);

  ++it;

  ASSERT_EQ(it, aboba.end());
}

TEST(test_map, constructor_4) {
  s21::map<int, std::string> opa{{1, "aboba"}, {2, "wuba"}, {3, "luba"}};
  s21::map<int, std::string> aboba(opa);

  EXPECT_FALSE(opa.empty());
  ASSERT_EQ(opa.size(), 3);

  auto it = opa.begin();

  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "aboba");

  ++it;

  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, "wuba");
  ++it;

  ASSERT_EQ(it->first, 3);
  ASSERT_EQ(it->second, "luba");

  ++it;

  ASSERT_EQ(it, opa.end());

  EXPECT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 3);

  it = aboba.begin();

  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "aboba");

  ++it;

  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, "wuba");

  ++it;

  ASSERT_EQ(it->first, 3);
  ASSERT_EQ(it->second, "luba");

  ++it;

  ASSERT_EQ(it, aboba.end());
}

TEST(test_map, constructor_5) {
  s21::map<double, std::string> opa{
      {1.1234, "aboba"}, {2.2345, "wuba"}, {3.3456, "luba"}};
  s21::map<double, std::string> aboba(opa);

  EXPECT_FALSE(opa.empty());
  ASSERT_EQ(opa.size(), 3);

  auto it = opa.begin();

  ASSERT_EQ(it->first, 1.1234);
  ASSERT_EQ(it->second, "aboba");

  ++it;

  ASSERT_EQ(it->first, 2.2345);
  ASSERT_EQ(it->second, "wuba");
  ++it;

  ASSERT_EQ(it->first, 3.3456);
  ASSERT_EQ(it->second, "luba");

  ++it;

  ASSERT_EQ(it, opa.end());

  EXPECT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 3);

  it = aboba.begin();

  ASSERT_EQ(it->first, 1.1234);
  ASSERT_EQ(it->second, "aboba");

  ++it;

  ASSERT_EQ(it->first, 2.2345);
  ASSERT_EQ(it->second, "wuba");

  ++it;

  ASSERT_EQ(it->first, 3.3456);
  ASSERT_EQ(it->second, "luba");

  ++it;

  ASSERT_EQ(it, aboba.end());
}

TEST(test_map, constructor_6) {
  s21::map<std::string, std::string> opa{
      {"aboba", "aboba"}, {"aboba", "aboba"}, {"wubaluba", "aboba"}};

  auto it = opa.begin();

  EXPECT_FALSE(opa.empty());
  ASSERT_EQ(opa.size(), 2);

  it = opa.begin();

  ASSERT_EQ(it->first, "aboba");
  ASSERT_EQ(it->second, "aboba");

  ++it;

  ASSERT_EQ(it->first, "wubaluba");
  ASSERT_EQ(it->second, "aboba");

  ++it;

  ASSERT_EQ(it, opa.end());
}

TEST(test_map, constructor_7) {
  std::list<int> stand(3);

  s21::map<std::string, std::list<int>> opa{{"aboba", stand}};

  EXPECT_FALSE(opa.empty());
  ASSERT_EQ(opa.size(), 1);

  auto it = opa.begin();

  ASSERT_EQ(it->first, "aboba");
  ASSERT_EQ(it->second, stand);

  int buddy = *it->second.begin();

  ASSERT_EQ(buddy, 0);

  ++it;

  ASSERT_EQ(it, opa.end());
}

TEST(test_map, constructor_8) {
  s21::map<int, int> aboba{
      {1, 1}, {100, 100000}, {-500, int()}, {-6000, -500000}, {-1, 1000}};
  s21::map<int, int> amogus(std::move(aboba));

  ASSERT_TRUE(aboba.empty());
  ASSERT_FALSE(amogus.empty());
  ASSERT_EQ(aboba.size(), 0);
  ASSERT_EQ(amogus.size(), 5);
}

TEST(test_map, constructor_9) {
  s21::map<std::string, int> aboba{
      {"acorn_apple", 1023},        {"banana_bread", 2046},
      {"candy_cane", 3500},         {"delta_dawn", 1500},
      {"eagle_eye", 4900},          {"falcon_flight", 1600},
      {"grape_grove", 3700},        {"honey_hive", 1800},
      {"iguana_ink", 2900},         {"jelly_jam", 5000},
      {"kite_knight", 2100},        {"lemon_lake", 3600},
      {"mango_moon", 2200},         {"nectar_nest", 5700},
      {"orange_oak", 3300},         {"peach_pond", 1200},
      {"quince_quill", 6600},       {"raspberry_rain", 4400},
      {"strawberry_sky", 2800},     {"tangerine_tide", 6000},
      {"umbrella_undulate", 4300},  {"violet_valley", 1400},
      {"watermelon_wave", 6200},    {"xylophone_xanadu", 5300},
      {"yam_yard", 4700},           {"zebra_zone", 3500},
      {"algebra_angle", 3100},      {"binary_bounce", 4100},
      {"calculus_curve", 5200},     {"delta_divide", 4800},
      {"epsilon_edge", 2500},       {"factor_field", 3900},
      {"geometry_gem", 3400},       {"hyperbola_horizon", 2700},
      {"integral_idea", 6100},      {"jungle_jog", 5400},
      {"kappa_key", 4500},          {"lambda_lattice", 6000},
      {"matrix_math", 6200},        {"number_node", 2900},
      {"omega_orbit", 5800},        {"pi_point", 2300},
      {"quadratic_quick", 2600},    {"radius_rhythm", 5100},
      {"sigma_summit", 3300},       {"theta_tangent", 4000},
      {"unitary_union", 5300},      {"vector_vortex", 2200},
      {"waveform_width", 5400},     {"xenon_xeno", 2500},
      {"yellow_yolk", 3900},        {"zephyr_zoom", 5100},
      {"astronaut_asteroid", 2000}, {"bionic_boom", 4100},
      {"cosmic_comet", 3200},       {"dynamic_dust", 2700},
      {"electric_eel", 4800},       {"fusion_forest", 5500},
      {"galaxy_gate", 5700},        {"hydro_hull", 5900},
      {"interstellar_ice", 6200},   {"jupiter_junction", 4300},
      {"kinetic_kingdom", 2500},    {"lunar_light", 3400},
      {"meteor_mind", 4600},        {"nebula_night", 6400},
      {"orbit_origin", 3300},       {"planet_peak", 3000},
      {"quantum_quasar", 5200},     {"rocket_rain", 3700},
      {"satellite_sail", 4500},     {"telescope_tunnel", 5300},
      {"universe_union", 6700},     {"venus_venture", 2100},
      {"wormhole_wonder", 5600},    {"xenon_xenon", 3500},
      {"yellow_yonder", 4200},      {"zenith_zone", 5800},
      {"alpha_apple", 6100},        {"bravo_banana", 4700},
      {"charlie_cherry", 5400},     {"delta_dragonfruit", 3900},
      {"echo_elderberry", 4500},    {"foxtrot_fig", 6200},
      {"golf_grape", 6700},         {"hotel_huckleberry", 5300},
      {"india_ice", 2900},          {"juliet_jackfruit", 4600},
      {"kilo_kiwi", 4200},          {"lima_lemon", 3100},
      {"mike_mango", 5600},         {"november_nectarine", 3600},
      {"oscar_orange", 4700},       {"papa_papaya", 3900},
      {"quebec_quince", 5100},      {"romeo_raspberry", 3200},
      {"sierra_strawberry", 3500},  {"tango_tangerine", 4400},
      {"uniform_ugli", 5200},       {"victor_vanilla", 3300},
      {"whiskey_watermelon", 4800}, {"x-ray_xigua", 5500},
      {"yankee_yam", 4300},         {"zulu_zucchini", 5700}};

  s21::map<std::string, int> amogus(std::move(aboba));

  ASSERT_TRUE(aboba.empty());
  ASSERT_FALSE(amogus.empty());
  ASSERT_EQ(aboba.size(), 0);
  ASSERT_EQ(amogus.size(), 104);
}

TEST(test_map, constructor_10) {
  s21::map<int, int> aboba{
      {1, 1}, {100, 100000}, {-500, int()}, {-6000, -500000}, {-1, 1000}};

  ASSERT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 5);

  s21::map<s21::map<int, int>, int> bola{{aboba, 1}};

  ASSERT_FALSE(bola.empty());
  ASSERT_EQ(bola.size(), 1);
}

TEST(test_map, equation_operator_1) {
  s21::map<int, int> opa{{1, 1}, {2, 12}, {3, 13}};
  s21::map<int, int> aboba;

  EXPECT_TRUE(aboba.empty());
  ASSERT_EQ(aboba.size(), 0);
  ASSERT_EQ(aboba.begin(), aboba.end());

  aboba = opa;
  bool comp = opa.begin() == opa.end();

  EXPECT_FALSE(opa.empty());
  ASSERT_EQ(opa.size(), 3);
  ASSERT_FALSE(comp);

  comp = aboba.begin() == aboba.end();

  EXPECT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 3);
  ASSERT_FALSE(comp);

  auto it = opa.begin();

  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, 1);

  ++it;

  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, 12);

  ++it;

  ASSERT_EQ(it->first, 3);
  ASSERT_EQ(it->second, 13);

  ++it;

  ASSERT_EQ(it, opa.end());

  it = aboba.begin();

  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, 1);

  ++it;

  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, 12);

  ++it;

  ASSERT_EQ(it->first, 3);
  ASSERT_EQ(it->second, 13);

  ++it;

  ASSERT_EQ(it, aboba.end());
}

TEST(test_map, equation_operator_2) {
  std::list<int> stand(3);
  s21::map<int, std::list<int>> aboba{{1, stand}};
  s21::map<int, std::list<int>> wuba;

  EXPECT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 1);
  ASSERT_FALSE(aboba.begin() == aboba.end());

  EXPECT_TRUE(wuba.empty());
  ASSERT_EQ(wuba.size(), 0);
  ASSERT_EQ(wuba.begin(), wuba.end());

  wuba = aboba;

  EXPECT_FALSE(wuba.empty());
  ASSERT_EQ(wuba.size(), 1);
  ASSERT_FALSE(wuba.begin() == wuba.end());

  auto it = wuba.begin();

  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, stand);
}

TEST(test_map, equation_opeartor_3) {
  s21::map<int, int> aboba{{1, 10}, {2, 11}, {2, 14}, {3, 17}};
  s21::map<int, int> wuba{{100, 190}, {99, 12}, {12, 13}, {120, 13}};

  wuba = aboba;

  ASSERT_EQ(aboba.size(), 3);

  auto ita = aboba.begin();
  auto itw = wuba.begin();

  EXPECT_EQ(ita->first, 1);
  EXPECT_EQ(ita->second, 10);
  EXPECT_EQ(itw->first, 1);
  EXPECT_EQ(itw->second, 10);

  ++ita;
  ++itw;

  EXPECT_EQ(ita->first, 2);
  EXPECT_EQ(ita->second, 11);
  EXPECT_EQ(itw->first, 2);
  EXPECT_EQ(itw->second, 11);

  ++ita;
  ++itw;

  EXPECT_EQ(ita->first, 3);
  EXPECT_EQ(ita->second, 17);
  EXPECT_EQ(itw->first, 3);
  EXPECT_EQ(itw->second, 17);

  ++ita;
  ++itw;

  EXPECT_EQ(ita, aboba.end());
  EXPECT_EQ(itw, wuba.end());
}

TEST(test_map, equation_opeartor_4) {
  s21::map<int, int> aboba{{1, 10}, {2, 11}, {2, 14}, {3, 17}};
  s21::map<int, int> wuba{{100, 190}, {99, 12}, {12, 13}, {120, 13}};

  wuba = std::move(aboba);

  ASSERT_TRUE(aboba.empty());
  ASSERT_EQ(aboba.size(), 0);
  ASSERT_EQ(aboba.begin(), aboba.end());

  auto it = wuba.begin();

  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, 10);

  ++it;

  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(it->second, 11);

  ++it;

  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, 17);

  ++it;

  EXPECT_EQ(it, wuba.end());
}

TEST(test_map, equation_opeartor_5) {
  s21::map<std::string, std::string> aboba{
      {"aboba", "wuber"}, {"guff", "sup"}, {"user", "name"}};
  s21::map<std::string, std::string> wuba{{"Goland", "Frozen"},
                                          {"golang", "c++"}};

  wuba = std::move(aboba);

  ASSERT_TRUE(aboba.empty());
  ASSERT_EQ(aboba.size(), 0);
  ASSERT_EQ(aboba.begin(), aboba.end());

  auto it = wuba.begin();

  EXPECT_EQ(it->first, "aboba");
  EXPECT_EQ(it->second, "wuber");

  ++it;

  EXPECT_EQ(it->first, "guff");
  EXPECT_EQ(it->second, "sup");

  ++it;

  EXPECT_EQ(it->first, "user");
  EXPECT_EQ(it->second, "name");

  ++it;

  EXPECT_EQ(it, wuba.end());
}

TEST(test_map, equation_operator_6) {
  std::map<std::string, std::string> gufi{{"gufi", "goober"},
                                          {"patrik", "snak"}};
  std::map<int, int> sec{{1, 1}, {1939, 1945}, {1337, 228}};
  s21::map<std::map<std::string, std::string>, std::map<int, int>> aboba{
      {gufi, sec}};
  s21::map<std::map<std::string, std::string>, std::map<int, int>> glob;

  ASSERT_FALSE(aboba.empty());
  ASSERT_FALSE(aboba.begin() == aboba.end());
  ASSERT_EQ(aboba.size(), 1);

  ASSERT_TRUE(glob.empty());
  ASSERT_TRUE(glob.begin() == glob.end());
  ASSERT_EQ(glob.size(), 0);

  glob = std::move(aboba);

  ASSERT_FALSE(glob.empty());
  ASSERT_FALSE(glob.begin() == glob.end());
  ASSERT_EQ(glob.size(), 1);

  ASSERT_TRUE(aboba.empty());
  ASSERT_TRUE(aboba.begin() == aboba.end());
  ASSERT_EQ(aboba.size(), 0);

  auto it = glob.begin();

  EXPECT_EQ(it->first.begin()->first, "gufi");
  EXPECT_EQ(it->second.begin()->first, 1);

  ++it;

  EXPECT_EQ(it, glob.end());
}

TEST(test_map, at_1) {
  s21::map<int, int> aboba{{1, 1}, {2, 6}, {3, 7}, {4, 8}};

  int creep = 0;
  ASSERT_NO_THROW(creep = aboba.at(2));

  ASSERT_EQ(creep, 6);
}

TEST(test_map, at_2) {
  s21::map<int, int> aboba{{1, 1}, {2, 6}, {3, 7}, {4, 8}};

  ASSERT_ANY_THROW(aboba.at(7));
}

TEST(test_map, at_3) {
  s21::map<int, int> aboba;

  ASSERT_TRUE(aboba.empty());
  ASSERT_EQ(aboba.size(), 0);
  ASSERT_EQ(aboba.begin(), aboba.end());
  ASSERT_ANY_THROW(aboba.at(7));
}

TEST(test_map, at_4) {
  s21::map<std::string, double> aboba{
      {"gold", 10000}, {"wood", 100.50}, {"nil", 0.001}, {"arrow", 15.25}};

  double creep = 0.0;
  ASSERT_NO_THROW(creep = aboba.at("arrow"));
  EXPECT_DOUBLE_EQ(creep, 15.25);
}

TEST(test_map, at_5) {
  std::list<std::string> lober{{"amogus"}};
  std::list<std::string> gimer;
  s21::map<std::string, std::list<std::string>> aboba{
      {"gold", lober}, {"wood", lober}, {"nil", lober}, {"arrow", lober}};

  ASSERT_NO_THROW(gimer = aboba.at("arrow"));
  EXPECT_EQ(gimer, lober);
}

TEST(test_map, at_6) {
  s21::map<std::string, int> gup{
      {"key1", 1},   {"key2", 2},   {"key3", 3},   {"key4", 4},
      {"key5", 5},   {"key6", 6},   {"key7", 7},   {"key8", 8},
      {"key9", 9},   {"key10", 10}, {"key11", 11}, {"key12", 12},
      {"key13", 13}, {"key14", 14}, {"key15", 15}, {"key16", 16},
      {"key17", 17}, {"key18", 18}, {"key19", 19}, {"key20", 20},
      {"key21", 21}, {"key22", 22}, {"key23", 23}, {"key24", 24},
      {"key25", 25}, {"key26", 26}, {"key27", 27}, {"key28", 28},
      {"key29", 29}, {"key30", 30}, {"key31", 31}, {"key32", 32},
      {"key33", 33}, {"key34", 34}, {"key35", 35}, {"key36", 36},
      {"key37", 37}, {"key38", 38}, {"key39", 39}, {"key40", 40},
      {"key41", 41}, {"key42", 42}, {"key43", 43}, {"key44", 44},
      {"key45", 45}, {"key46", 46}, {"key47", 47}, {"key48", 48},
      {"key49", 49}, {"key50", 50}, {"key51", 51}, {"key52", 52},
      {"key53", 53}, {"key54", 54}, {"key55", 55}, {"key56", 56},
      {"key57", 57}, {"key58", 58}, {"key59", 59}, {"key60", 60},
      {"key61", 61}, {"key62", 62}, {"key63", 63}, {"key64", 64},
      {"key65", 65}, {"key66", 66}, {"key67", 67}, {"key68", 68},
      {"key69", 69}, {"key70", 70}, {"key71", 71}, {"key72", 72},
      {"key73", 73}, {"key74", 74}, {"key75", 75}, {"key76", 76},
      {"key77", 77}, {"key78", 78}, {"key79", 79}, {"key80", 80},
      {"key81", 81}, {"key82", 82}, {"key83", 83}, {"key84", 84},
      {"key85", 85}, {"key86", 86}, {"key87", 87}, {"key88", 88},
      {"key89", 89}, {"key90", 90}, {"key91", 91}, {"key92", 92},
      {"key93", 93}, {"key94", 94}, {"key95", 95}, {"key96", 96},
      {"key97", 97}, {"key98", 98}, {"key99", 99}, {"key100", 100}};

  int creep = int();

  ASSERT_NO_THROW(creep = gup.at("key82"));
  ASSERT_EQ(creep, 82);
}

TEST(test_map, at_7) {
  s21::map<std::string, int> gup{
      {"key1", 1},   {"key2", 2},   {"key3", 3},   {"key4", 4},
      {"key5", 5},   {"key6", 6},   {"key7", 7},   {"key8", 8},
      {"key9", 9},   {"key10", 10}, {"key11", 11}, {"key12", 12},
      {"key13", 13}, {"key14", 14}, {"key15", 15}, {"key16", 16},
      {"key17", 17}, {"key18", 18}, {"key19", 19}, {"key20", 20},
      {"key21", 21}, {"key22", 22}, {"key23", 23}, {"key24", 24},
      {"key25", 25}, {"key26", 26}, {"key27", 27}, {"key28", 28},
      {"key29", 29}, {"key30", 30}, {"key31", 31}, {"key32", 32},
      {"key33", 33}, {"key34", 34}, {"key35", 35}, {"key36", 36},
      {"key37", 37}, {"key38", 38}, {"key39", 39}, {"key40", 40},
      {"key41", 41}, {"key42", 42}, {"key43", 43}, {"key44", 44},
      {"key45", 45}, {"key46", 46}, {"key47", 47}, {"key48", 48},
      {"key49", 49}, {"key50", 50}, {"key51", 51}, {"key52", 52},
      {"key53", 53}, {"key54", 54}, {"key55", 55}, {"key56", 56},
      {"key57", 57}, {"key58", 58}, {"key59", 59}, {"key60", 60},
      {"key61", 61}, {"key62", 62}, {"key63", 63}, {"key64", 64},
      {"key65", 65}, {"key66", 66}, {"key67", 67}, {"key68", 68},
      {"key69", 69}, {"key70", 70}, {"key71", 71}, {"key72", 72},
      {"key73", 73}, {"key74", 74}, {"key75", 75}, {"key76", 76},
      {"key77", 77}, {"key78", 78}, {"key79", 79}, {"key80", 80},
      {"key81", 81}, {"key82", 82}, {"key83", 83}, {"key84", 84},
      {"key85", 85}, {"key86", 86}, {"key87", 87}, {"key88", 88},
      {"key89", 89}, {"key90", 90}, {"key91", 91}, {"key92", 92},
      {"key93", 93}, {"key94", 94}, {"key95", 95}, {"key96", 96},
      {"key97", 97}, {"key98", 98}, {"key99", 99}, {"key100", 100}};

  ASSERT_ANY_THROW(gup.at("key111"));
}

TEST(test_map, at_8) {
  s21::map<std::string, int> ballun{
      {"acorn_apple", 1023},        {"banana_bread", 2046},
      {"candy_cane", 3500},         {"delta_dawn", 1500},
      {"eagle_eye", 4900},          {"falcon_flight", 1600},
      {"grape_grove", 3700},        {"honey_hive", 1800},
      {"iguana_ink", 2900},         {"jelly_jam", 5000},
      {"kite_knight", 2100},        {"lemon_lake", 3600},
      {"mango_moon", 2200},         {"nectar_nest", 5700},
      {"orange_oak", 3300},         {"peach_pond", 1200},
      {"quince_quill", 6600},       {"raspberry_rain", 4400},
      {"strawberry_sky", 2800},     {"tangerine_tide", 6000},
      {"umbrella_undulate", 4300},  {"violet_valley", 1400},
      {"watermelon_wave", 6200},    {"xylophone_xanadu", 5300},
      {"yam_yard", 4700},           {"zebra_zone", 3500},
      {"algebra_angle", 3100},      {"binary_bounce", 4100},
      {"calculus_curve", 5200},     {"delta_divide", 4800},
      {"epsilon_edge", 2500},       {"factor_field", 3900},
      {"geometry_gem", 3400},       {"hyperbola_horizon", 2700},
      {"integral_idea", 6100},      {"jungle_jog", 5400},
      {"kappa_key", 4500},          {"lambda_lattice", 6000},
      {"matrix_math", 6200},        {"number_node", 2900},
      {"omega_orbit", 5800},        {"pi_point", 2300},
      {"quadratic_quick", 2600},    {"radius_rhythm", 5100},
      {"sigma_summit", 3300},       {"theta_tangent", 4000},
      {"unitary_union", 5300},      {"vector_vortex", 2200},
      {"waveform_width", 5400},     {"xenon_xeno", 2500},
      {"yellow_yolk", 3900},        {"zephyr_zoom", 5100},
      {"astronaut_asteroid", 2000}, {"bionic_boom", 4100},
      {"cosmic_comet", 3200},       {"dynamic_dust", 2700},
      {"electric_eel", 4800},       {"fusion_forest", 5500},
      {"galaxy_gate", 5700},        {"hydro_hull", 5900},
      {"interstellar_ice", 6200},   {"jupiter_junction", 4300},
      {"kinetic_kingdom", 2500},    {"lunar_light", 3400},
      {"meteor_mind", 4600},        {"nebula_night", 6400},
      {"orbit_origin", 3300},       {"planet_peak", 3000},
      {"quantum_quasar", 5200},     {"rocket_rain", 3700},
      {"satellite_sail", 4500},     {"telescope_tunnel", 5300},
      {"universe_union", 6700},     {"venus_venture", 2100},
      {"wormhole_wonder", 5600},    {"xenon_xenon", 3500},
      {"yellow_yonder", 4200},      {"zenith_zone", 5800},
      {"alpha_apple", 6100},        {"bravo_banana", 4700},
      {"charlie_cherry", 5400},     {"delta_dragonfruit", 3900},
      {"echo_elderberry", 4500},    {"foxtrot_fig", 6200},
      {"golf_grape", 6700},         {"hotel_huckleberry", 5300},
      {"india_ice", 2900},          {"juliet_jackfruit", 4600},
      {"kilo_kiwi", 4200},          {"lima_lemon", 3100},
      {"mike_mango", 5600},         {"november_nectarine", 3600},
      {"oscar_orange", 4700},       {"papa_papaya", 3900},
      {"quebec_quince", 5100},      {"romeo_raspberry", 3200},
      {"sierra_strawberry", 3500},  {"tango_tangerine", 4400},
      {"uniform_ugli", 5200},       {"victor_vanilla", 3300},
      {"whiskey_watermelon", 4800}, {"x-ray_xigua", 5500},
      {"yankee_yam", 4300},         {"zulu_zucchini", 5700}};

  int creep = int();

  ASSERT_NO_THROW(creep = ballun.at("zulu_zucchini"));
  ASSERT_EQ(creep, 5700);
}

TEST(test_map, at_9) {
  s21::map<std::string, int> ballun{
      {"acorn_apple", 1023},        {"banana_bread", 2046},
      {"candy_cane", 3500},         {"delta_dawn", 1500},
      {"eagle_eye", 4900},          {"falcon_flight", 1600},
      {"grape_grove", 3700},        {"honey_hive", 1800},
      {"iguana_ink", 2900},         {"jelly_jam", 5000},
      {"kite_knight", 2100},        {"lemon_lake", 3600},
      {"mango_moon", 2200},         {"nectar_nest", 5700},
      {"orange_oak", 3300},         {"peach_pond", 1200},
      {"quince_quill", 6600},       {"raspberry_rain", 4400},
      {"strawberry_sky", 2800},     {"tangerine_tide", 6000},
      {"umbrella_undulate", 4300},  {"violet_valley", 1400},
      {"watermelon_wave", 6200},    {"xylophone_xanadu", 5300},
      {"yam_yard", 4700},           {"zebra_zone", 3500},
      {"algebra_angle", 3100},      {"binary_bounce", 4100},
      {"calculus_curve", 5200},     {"delta_divide", 4800},
      {"epsilon_edge", 2500},       {"factor_field", 3900},
      {"geometry_gem", 3400},       {"hyperbola_horizon", 2700},
      {"integral_idea", 6100},      {"jungle_jog", 5400},
      {"kappa_key", 4500},          {"lambda_lattice", 6000},
      {"matrix_math", 6200},        {"number_node", 2900},
      {"omega_orbit", 5800},        {"pi_point", 2300},
      {"quadratic_quick", 2600},    {"radius_rhythm", 5100},
      {"sigma_summit", 3300},       {"theta_tangent", 4000},
      {"unitary_union", 5300},      {"vector_vortex", 2200},
      {"waveform_width", 5400},     {"xenon_xeno", 2500},
      {"yellow_yolk", 3900},        {"zephyr_zoom", 5100},
      {"astronaut_asteroid", 2000}, {"bionic_boom", 4100},
      {"cosmic_comet", 3200},       {"dynamic_dust", 2700},
      {"electric_eel", 4800},       {"fusion_forest", 5500},
      {"galaxy_gate", 5700},        {"hydro_hull", 5900},
      {"interstellar_ice", 6200},   {"jupiter_junction", 4300},
      {"kinetic_kingdom", 2500},    {"lunar_light", 3400},
      {"meteor_mind", 4600},        {"nebula_night", 6400},
      {"orbit_origin", 3300},       {"planet_peak", 3000},
      {"quantum_quasar", 5200},     {"rocket_rain", 3700},
      {"satellite_sail", 4500},     {"telescope_tunnel", 5300},
      {"universe_union", 6700},     {"venus_venture", 2100},
      {"wormhole_wonder", 5600},    {"xenon_xenon", 3500},
      {"yellow_yonder", 4200},      {"zenith_zone", 5800},
      {"alpha_apple", 6100},        {"bravo_banana", 4700},
      {"charlie_cherry", 5400},     {"delta_dragonfruit", 3900},
      {"echo_elderberry", 4500},    {"foxtrot_fig", 6200},
      {"golf_grape", 6700},         {"hotel_huckleberry", 5300},
      {"india_ice", 2900},          {"juliet_jackfruit", 4600},
      {"kilo_kiwi", 4200},          {"lima_lemon", 3100},
      {"mike_mango", 5600},         {"november_nectarine", 3600},
      {"oscar_orange", 4700},       {"papa_papaya", 3900},
      {"quebec_quince", 5100},      {"romeo_raspberry", 3200},
      {"sierra_strawberry", 3500},  {"tango_tangerine", 4400},
      {"uniform_ugli", 5200},       {"victor_vanilla", 3300},
      {"whiskey_watermelon", 4800}, {"x-ray_xigua", 5500},
      {"yankee_yam", 4300},         {"zulu_zucchini", 5700}};

  ASSERT_ANY_THROW(ballun.at("ALLOHA"));
}

TEST(test_map, index_operator_1) {
  s21::map<std::string, int> aboba;
  std::string key = "key";

  for (int i = 0; i < 10000; ++i) {
    key += std::to_string(i);
    aboba[key] = i;
    key = "key";
  }

  int creep = int();
  ASSERT_NO_THROW(creep = aboba.at("key9999"));
  ASSERT_EQ(creep, 9999);
}

TEST(test_map, index_operator_1_std) {
  std::map<std::string, int> aboba;
  std::string key = "key";

  for (int i = 0; i < 10000; ++i) {
    key += std::to_string(i);
    aboba[key] = i;
    key = "key";
  }

  int creep = int();
  ASSERT_NO_THROW(creep = aboba.at("key9999"));
  ASSERT_EQ(creep, 9999);
}

TEST(test_map, index_operator_2) {
  s21::map<std::string, int> ballun{
      {"acorn_apple", 1023},        {"banana_bread", 2046},
      {"candy_cane", 3500},         {"delta_dawn", 1500},
      {"eagle_eye", 4900},          {"falcon_flight", 1600},
      {"grape_grove", 3700},        {"honey_hive", 1800},
      {"iguana_ink", 2900},         {"jelly_jam", 5000},
      {"kite_knight", 2100},        {"lemon_lake", 3600},
      {"mango_moon", 2200},         {"nectar_nest", 5700},
      {"orange_oak", 3300},         {"peach_pond", 1200},
      {"quince_quill", 6600},       {"raspberry_rain", 4400},
      {"strawberry_sky", 2800},     {"tangerine_tide", 6000},
      {"umbrella_undulate", 4300},  {"violet_valley", 1400},
      {"watermelon_wave", 6200},    {"xylophone_xanadu", 5300},
      {"yam_yard", 4700},           {"zebra_zone", 3500},
      {"algebra_angle", 3100},      {"binary_bounce", 4100},
      {"calculus_curve", 5200},     {"delta_divide", 4800},
      {"epsilon_edge", 2500},       {"factor_field", 3900},
      {"geometry_gem", 3400},       {"hyperbola_horizon", 2700},
      {"integral_idea", 6100},      {"jungle_jog", 5400},
      {"kappa_key", 4500},          {"lambda_lattice", 6000},
      {"matrix_math", 6200},        {"number_node", 2900},
      {"omega_orbit", 5800},        {"pi_point", 2300},
      {"quadratic_quick", 2600},    {"radius_rhythm", 5100},
      {"sigma_summit", 3300},       {"theta_tangent", 4000},
      {"unitary_union", 5300},      {"vector_vortex", 2200},
      {"waveform_width", 5400},     {"xenon_xeno", 2500},
      {"yellow_yolk", 3900},        {"zephyr_zoom", 5100},
      {"astronaut_asteroid", 2000}, {"bionic_boom", 4100},
      {"cosmic_comet", 3200},       {"dynamic_dust", 2700},
      {"electric_eel", 4800},       {"fusion_forest", 5500},
      {"galaxy_gate", 5700},        {"hydro_hull", 5900},
      {"interstellar_ice", 6200},   {"jupiter_junction", 4300},
      {"kinetic_kingdom", 2500},    {"lunar_light", 3400},
      {"meteor_mind", 4600},        {"nebula_night", 6400},
      {"orbit_origin", 3300},       {"planet_peak", 3000},
      {"quantum_quasar", 5200},     {"rocket_rain", 3700},
      {"satellite_sail", 4500},     {"telescope_tunnel", 5300},
      {"universe_union", 6700},     {"venus_venture", 2100},
      {"wormhole_wonder", 5600},    {"xenon_xenon", 3500},
      {"yellow_yonder", 4200},      {"zenith_zone", 5800},
      {"alpha_apple", 6100},        {"bravo_banana", 4700},
      {"charlie_cherry", 5400},     {"delta_dragonfruit", 3900},
      {"echo_elderberry", 4500},    {"foxtrot_fig", 6200},
      {"golf_grape", 6700},         {"hotel_huckleberry", 5300},
      {"india_ice", 2900},          {"juliet_jackfruit", 4600},
      {"kilo_kiwi", 4200},          {"lima_lemon", 3100},
      {"mike_mango", 5600},         {"november_nectarine", 3600},
      {"oscar_orange", 4700},       {"papa_papaya", 3900},
      {"quebec_quince", 5100},      {"romeo_raspberry", 3200},
      {"sierra_strawberry", 3500},  {"tango_tangerine", 4400},
      {"uniform_ugli", 5200},       {"victor_vanilla", 3300},
      {"whiskey_watermelon", 4800}, {"x-ray_xigua", 5500},
      {"yankee_yam", 4300},         {"zulu_zucchini", 5700}};

  EXPECT_EQ(ballun["bionic_boom"], 4100);
}

TEST(test_map, begin_1) {
  s21::map<int, int> aboba{{1, 1},   {2, 10},  {3, 100},
                           {4, 600}, {5, 800}, {6, 1}};

  ASSERT_EQ(aboba.begin()->first, 1);
}

TEST(test_map, begin_2) {
  s21::map<int, int> aboba;

  ASSERT_EQ(aboba.begin(), aboba.end());
}

TEST(test_map, begin_3) {
  s21::map<int, int> aboba;

  auto it = aboba.begin();

  ASSERT_EQ(it, aboba.end());
}

TEST(test_map, end_1) {
  s21::map<std::string, int> aboba{
      {"acorn_apple", 1023},        {"banana_bread", 2046},
      {"candy_cane", 3500},         {"delta_dawn", 1500},
      {"eagle_eye", 4900},          {"falcon_flight", 1600},
      {"grape_grove", 3700},        {"honey_hive", 1800},
      {"iguana_ink", 2900},         {"jelly_jam", 5000},
      {"kite_knight", 2100},        {"lemon_lake", 3600},
      {"mango_moon", 2200},         {"nectar_nest", 5700},
      {"orange_oak", 3300},         {"peach_pond", 1200},
      {"quince_quill", 6600},       {"raspberry_rain", 4400},
      {"strawberry_sky", 2800},     {"tangerine_tide", 6000},
      {"umbrella_undulate", 4300},  {"violet_valley", 1400},
      {"watermelon_wave", 6200},    {"xylophone_xanadu", 5300},
      {"yam_yard", 4700},           {"zebra_zone", 3500},
      {"algebra_angle", 3100},      {"binary_bounce", 4100},
      {"calculus_curve", 5200},     {"delta_divide", 4800},
      {"epsilon_edge", 2500},       {"factor_field", 3900},
      {"geometry_gem", 3400},       {"hyperbola_horizon", 2700},
      {"integral_idea", 6100},      {"jungle_jog", 5400},
      {"kappa_key", 4500},          {"lambda_lattice", 6000},
      {"matrix_math", 6200},        {"number_node", 2900},
      {"omega_orbit", 5800},        {"pi_point", 2300},
      {"quadratic_quick", 2600},    {"radius_rhythm", 5100},
      {"sigma_summit", 3300},       {"theta_tangent", 4000},
      {"unitary_union", 5300},      {"vector_vortex", 2200},
      {"waveform_width", 5400},     {"xenon_xeno", 2500},
      {"yellow_yolk", 3900},        {"zephyr_zoom", 5100},
      {"astronaut_asteroid", 2000}, {"bionic_boom", 4100},
      {"cosmic_comet", 3200},       {"dynamic_dust", 2700},
      {"electric_eel", 4800},       {"fusion_forest", 5500},
      {"galaxy_gate", 5700},        {"hydro_hull", 5900},
      {"interstellar_ice", 6200},   {"jupiter_junction", 4300},
      {"kinetic_kingdom", 2500},    {"lunar_light", 3400},
      {"meteor_mind", 4600},        {"nebula_night", 6400},
      {"orbit_origin", 3300},       {"planet_peak", 3000},
      {"quantum_quasar", 5200},     {"rocket_rain", 3700},
      {"satellite_sail", 4500},     {"telescope_tunnel", 5300},
      {"universe_union", 6700},     {"venus_venture", 2100},
      {"wormhole_wonder", 5600},    {"xenon_xenon", 3500},
      {"yellow_yonder", 4200},      {"zenith_zone", 5800},
      {"alpha_apple", 6100},        {"bravo_banana", 4700},
      {"charlie_cherry", 5400},     {"delta_dragonfruit", 3900},
      {"echo_elderberry", 4500},    {"foxtrot_fig", 6200},
      {"golf_grape", 6700},         {"hotel_huckleberry", 5300},
      {"india_ice", 2900},          {"juliet_jackfruit", 4600},
      {"kilo_kiwi", 4200},          {"lima_lemon", 3100},
      {"mike_mango", 5600},         {"november_nectarine", 3600},
      {"oscar_orange", 4700},       {"papa_papaya", 3900},
      {"quebec_quince", 5100},      {"romeo_raspberry", 3200},
      {"sierra_strawberry", 3500},  {"tango_tangerine", 4400},
      {"uniform_ugli", 5200},       {"victor_vanilla", 3300},
      {"whiskey_watermelon", 4800}, {"x-ray_xigua", 5500},
      {"yankee_yam", 4300},         {"zulu_zucchini", 5700}};

  ASSERT_EQ((--aboba.end())->first, "zulu_zucchini");
}

TEST(test_map, end_2) {
  s21::map<std::string, int> aboba{
      {"acorn_apple", 1023},        {"banana_bread", 2046},
      {"candy_cane", 3500},         {"delta_dawn", 1500},
      {"eagle_eye", 4900},          {"falcon_flight", 1600},
      {"grape_grove", 3700},        {"honey_hive", 1800},
      {"iguana_ink", 2900},         {"jelly_jam", 5000},
      {"kite_knight", 2100},        {"lemon_lake", 3600},
      {"mango_moon", 2200},         {"nectar_nest", 5700},
      {"orange_oak", 3300},         {"peach_pond", 1200},
      {"quince_quill", 6600},       {"raspberry_rain", 4400},
      {"strawberry_sky", 2800},     {"tangerine_tide", 6000},
      {"umbrella_undulate", 4300},  {"violet_valley", 1400},
      {"watermelon_wave", 6200},    {"xylophone_xanadu", 5300},
      {"yam_yard", 4700},           {"zebra_zone", 3500},
      {"algebra_angle", 3100},      {"binary_bounce", 4100},
      {"calculus_curve", 5200},     {"delta_divide", 4800},
      {"epsilon_edge", 2500},       {"factor_field", 3900},
      {"geometry_gem", 3400},       {"hyperbola_horizon", 2700},
      {"integral_idea", 6100},      {"jungle_jog", 5400},
      {"kappa_key", 4500},          {"lambda_lattice", 6000},
      {"matrix_math", 6200},        {"number_node", 2900},
      {"omega_orbit", 5800},        {"pi_point", 2300},
      {"quadratic_quick", 2600},    {"radius_rhythm", 5100},
      {"sigma_summit", 3300},       {"theta_tangent", 4000},
      {"unitary_union", 5300},      {"vector_vortex", 2200},
      {"waveform_width", 5400},     {"xenon_xeno", 2500},
      {"yellow_yolk", 3900},        {"zephyr_zoom", 5100},
      {"astronaut_asteroid", 2000}, {"bionic_boom", 4100},
      {"cosmic_comet", 3200},       {"dynamic_dust", 2700},
      {"electric_eel", 4800},       {"fusion_forest", 5500},
      {"galaxy_gate", 5700},        {"hydro_hull", 5900},
      {"interstellar_ice", 6200},   {"jupiter_junction", 4300},
      {"kinetic_kingdom", 2500},    {"lunar_light", 3400},
      {"meteor_mind", 4600},        {"nebula_night", 6400},
      {"orbit_origin", 3300},       {"planet_peak", 3000},
      {"quantum_quasar", 5200},     {"rocket_rain", 3700},
      {"satellite_sail", 4500},     {"telescope_tunnel", 5300},
      {"universe_union", 6700},     {"venus_venture", 2100},
      {"wormhole_wonder", 5600},    {"xenon_xenon", 3500},
      {"yellow_yonder", 4200},      {"zenith_zone", 5800},
      {"alpha_apple", 6100},        {"bravo_banana", 4700},
      {"charlie_cherry", 5400},     {"delta_dragonfruit", 3900},
      {"echo_elderberry", 4500},    {"foxtrot_fig", 6200},
      {"golf_grape", 6700},         {"hotel_huckleberry", 5300},
      {"india_ice", 2900},          {"juliet_jackfruit", 4600},
      {"kilo_kiwi", 4200},          {"lima_lemon", 3100},
      {"mike_mango", 5600},         {"november_nectarine", 3600},
      {"oscar_orange", 4700},       {"papa_papaya", 3900},
      {"quebec_quince", 5100},      {"romeo_raspberry", 3200},
      {"sierra_strawberry", 3500},  {"tango_tangerine", 4400},
      {"uniform_ugli", 5200},       {"victor_vanilla", 3300},
      {"whiskey_watermelon", 4800}, {"x-ray_xigua", 5500},
      {"yankee_yam", 4300},         {"zulu_zucchini", 5700}};

  s21::map<std::string, int>::const_iterator it = aboba.cend();

  --it;

  ASSERT_EQ(it->first, "zulu_zucchini");
}

TEST(test_map, empty_1) {
  s21::map<int, int> opa;

  ASSERT_TRUE(opa.empty());
  ASSERT_EQ(opa.begin(), opa.end());
}

TEST(test_map, empty_2) {
  s21::map<int, int> opa{{1, 1}, {2, 1}, {3, 4}};
  s21::map<int, int> aboba;

  ASSERT_FALSE(opa.empty());
  ASSERT_FALSE(opa.begin() == opa.end());
  ASSERT_TRUE(aboba.empty());
  ASSERT_EQ(aboba.begin(), aboba.end());

  aboba = std::move(opa);

  ASSERT_TRUE(opa.empty());
  ASSERT_EQ(opa.begin(), opa.end());
  ASSERT_FALSE(aboba.empty());
  ASSERT_FALSE(aboba.begin() == aboba.end());
}

TEST(test_map, empty_3) {
  s21::map<int, int> opa{{1, 1}, {2, 1}, {3, 4}};

  auto it = opa.begin();

  it = opa.erase(it);
  it = opa.erase(it);
  it = opa.erase(it);

  ASSERT_TRUE(opa.empty());
  ASSERT_EQ(opa.begin(), opa.end());
}

TEST(test_map, size_1) {
  s21::map<int, int> aboba;

  ASSERT_EQ(aboba.size(), 0);
}

TEST(test_map, size_2) {
  s21::map<int, int> boba{{1, 1}, {2, 3}, {3, 6}};

  ASSERT_EQ(boba.size(), 3);

  auto it = boba.begin();

  it = boba.erase(it);
  it = boba.erase(it);
  it = boba.erase(it);

  ASSERT_EQ(it, boba.end());
  ASSERT_EQ(boba.size(), 0);
}

TEST(test_map, size_3) {
  s21::map<std::string, std::string> aboba{{"g", "h"}, {"m", "k"}, {"g", "k"},
                                           {"k", "m"}, {"", ""},   {"", ","},
                                           {",", ","}};
  ASSERT_EQ(aboba.size(), 5);
}

TEST(test_map, size_4) {
  s21::map<std::string, std::string> aboba{{"g", "h"}, {"m", "k"}, {"g", "k"},
                                           {"k", "m"}, {"", ""},   {"", ","},
                                           {",", ","}};
  aboba.clear();
  ASSERT_EQ(aboba.size(), 0);
}

TEST(test_map, size_5) {
  s21::map<double, double> wubaluba{
      {1.0001, 100.100001}, {5, 8.0012301}, {-6.12, -9.09}};

  s21::map<double, double> luba;

  ASSERT_EQ(wubaluba.size(), 3);
  ASSERT_EQ(luba.size(), 0);

  luba = wubaluba;

  ASSERT_EQ(wubaluba.size(), 3);
  ASSERT_EQ(luba.size(), 3);
}

TEST(test_map, size_6) {
  s21::map<double, double> wubaluba{
      {1.0001, 100.100001}, {5, 8.0012301}, {-6.12, -9.09}};

  s21::map<double, double> luba;

  ASSERT_EQ(wubaluba.size(), 3);
  ASSERT_EQ(luba.size(), 0);

  luba = std::move(wubaluba);

  ASSERT_EQ(wubaluba.size(), 0);
  ASSERT_EQ(luba.size(), 3);
}

TEST(test_map, size_7) {
  s21::map<std::string, int> aboba;
  std::string key = "key";

  for (int i = 0; i < 10000; ++i) {
    key += std::to_string(i);
    aboba[key] = i;
    key = "key";
  }

  ASSERT_EQ(aboba.size(), 10000);
}

TEST(test_map, clear_1) {
  s21::map<std::string, int> aboba;
  std::string key = "key";

  for (int i = 0; i < 10000; ++i) {
    key += std::to_string(i);
    aboba[key] = i;
    key = "key";
  }

  ASSERT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 10000);

  aboba.clear();

  ASSERT_TRUE(aboba.empty());
  ASSERT_EQ(aboba.size(), 0);
}

TEST(test_map, clear_2) {
  s21::map<int, int> aboba;

  for (int i = 0; i < 10000; ++i) {
    aboba[i] = i;
  }

  ASSERT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 10000);

  aboba.clear();

  auto it = aboba.begin();
  ++it;

  ASSERT_TRUE(aboba.empty());
  ASSERT_EQ(it, aboba.begin());
  ASSERT_EQ(it, aboba.end());
  ASSERT_EQ(aboba.size(), 0);
}

TEST(test_map, max_size) {
  s21::map<int, int> aboba_s21;
  std::map<int, int> aboba_stl;

  ASSERT_EQ(aboba_s21.max_size(), aboba_stl.max_size());

  s21::map<std::string, int> amogus_s21;
  std::map<std::string, int> amogus_stl;

  ASSERT_EQ(amogus_s21.max_size(), amogus_stl.max_size());

  s21::map<int, double> gus_s21;
  std::map<int, double> gus_stl;

  ASSERT_EQ(gus_s21.max_size(), gus_stl.max_size());

  s21::map<char, double> amo_s21;
  std::map<char, double> amo_stl;

  ASSERT_EQ(amo_s21.max_size(), amo_stl.max_size());

  s21::map<std::list<int>, std::list<std::string>> gym_boss_s21;
  std::map<std::list<int>, std::list<std::string>> gym_boss_stl;

  ASSERT_EQ(gym_boss_s21.max_size(), gym_boss_stl.max_size());
}

TEST(test_map, insert_1) {
  s21::map<int, int> aboba;

  ASSERT_TRUE(aboba.empty());

  std::pair<s21::map<int, int>::iterator, bool> it = aboba.insert({1, 5});

  ASSERT_TRUE(it.second);
  ASSERT_EQ((it.first)->first, 1);
  ASSERT_EQ((it.first)->second, 5);
}

TEST(test_map, insert_2) {
  s21::map<int, int> aboba;

  ASSERT_TRUE(aboba.empty());

  std::pair<s21::map<int, int>::iterator, bool> it = aboba.insert({1, 5});

  ASSERT_TRUE(it.second);
  ASSERT_EQ((it.first)->first, 1);
  ASSERT_EQ((it.first)->second, 5);

  it = aboba.insert({1, 2});

  ASSERT_FALSE(it.second);
  ASSERT_EQ((it.first)->first, 1);
  ASSERT_EQ((it.first)->second, 5);
}

TEST(test_map, insert_3) {
  s21::map<std::string, int> aboba;

  ASSERT_TRUE(aboba.empty());

  std::pair<s21::map<std::string, int>::iterator, bool> it =
      aboba.insert({"guffi", 5});

  std::string creep = it.first->first;
  bool comp = creep == "guffi";

  ASSERT_TRUE(it.second);
  ASSERT_TRUE(comp);
  ASSERT_EQ((it.first)->second, 5);

  it = aboba.insert({"robber", 2});
  creep = it.first->first;
  comp = creep == "robber";

  ASSERT_TRUE(it.second);
  ASSERT_TRUE(comp);
  ASSERT_EQ((it.first)->second, 2);
}

TEST(test_map, insert_4) {
  s21::map<double, double> giber;

  std::pair<s21::map<double, double>::iterator, bool> controler =
      giber.insert({1.001, 99.1023});

  ASSERT_TRUE(controler.second);
  ASSERT_DOUBLE_EQ(controler.first->first, 1.001);
  ASSERT_DOUBLE_EQ(controler.first->second, 99.1023);
  EXPECT_EQ(giber.size(), 1);
  EXPECT_FALSE(giber.empty());

  controler = giber.insert({1.001, 99.1023});

  ASSERT_FALSE(controler.second);
  ASSERT_DOUBLE_EQ(controler.first->first, 1.001);
  ASSERT_DOUBLE_EQ(controler.first->second, 99.1023);
  EXPECT_EQ(giber.size(), 1);
  EXPECT_FALSE(giber.empty());
}

TEST(test_map, insert_5) {
  s21::map<int, int> kal;
  kal.insert({10, 10});
  kal.insert({5, 20});
  ASSERT_EQ(kal.size(), 2);
  ASSERT_EQ(kal.begin()->second, 20);
}

TEST(test_map, insert_6) {
  s21::map<int, int> kal;
  kal.insert({10, 10});
  kal.insert({15, 20});
  ASSERT_EQ(kal.size(), 2);
  ASSERT_EQ(kal.begin()->second, 10);
  ASSERT_EQ((--kal.end())->second, 20);
}

TEST(test_map, insert_7) {
  s21::map<int, int> kal;
  kal.insert({10, 10});
  kal.insert({20, 20});
  kal.insert({30, 30});

  ASSERT_EQ(kal.size(), 3);
  ASSERT_EQ(kal.begin()->first, 10);
  ASSERT_EQ((--kal.end())->first, 30);

  ASSERT_TRUE(kal.contains(10));
  ASSERT_TRUE(kal.contains(20));
  ASSERT_TRUE(kal.contains(30));
}

TEST(test_map, insert_8) {
  s21::map<std::string, int> kal;

  kal.insert({"delta", 1});
  kal.insert({"alpha", 2});
  kal.insert({"epsilon", 3});
  kal.insert({"beta", 4});
  kal.insert({"gamma", 5});

  ASSERT_EQ(kal.size(), 5);
  ASSERT_EQ(kal.begin()->first, "alpha");
  ASSERT_EQ((--kal.end())->first, "gamma");

  ASSERT_TRUE(kal.contains("delta"));
  ASSERT_TRUE(kal.contains("epsilon"));
  ASSERT_TRUE(kal.contains("alpha"));
  ASSERT_TRUE(kal.contains("beta"));
  ASSERT_TRUE(kal.contains("gamma"));
}

TEST(test_map, insert_9) {
  s21::map<std::string, int> aboba;
  const int element_num = 10000;
  std::vector<std::string> key_container;
  std::string key = "key";

  for (int i = 0; i < element_num; ++i) {
    key += i;
    key_container.push_back(key);
    aboba.insert({key, i});
    key = "key";
  }

  for (int i = 0; i < element_num; ++i) {
    ASSERT_TRUE(aboba.contains(key_container[i]));
  }
}

TEST(test_map, insert_mapped_value_1) {
  s21::map<int, int> aboba{{1, 1}, {3, 100}, {6000, -1231}, {888, 12314}};

  std::pair<s21::map<int, int>::iterator, bool> res = aboba.insert(888, -1);

  bool comp = res.first->second == 12314;

  ASSERT_TRUE(res.second);
  ASSERT_FALSE(comp);
  ASSERT_EQ(res.first->first, 888);
  ASSERT_EQ(aboba[888], -1);
}

TEST(test_map, insert_mapped_value_2) {
  s21::map<int, int> aboba{{1, 1}, {3, 100}, {6000, -1231}, {888, 12314}};

  std::pair<s21::map<int, int>::iterator, bool> res = aboba.insert(999, -1);

  ASSERT_FALSE(res.second);
  ASSERT_EQ(res.first, aboba.end());
  ASSERT_FALSE(aboba.contains(999));
}

TEST(test_map, insert_mapped_value_3) {
  s21::map<int, int> aboba;

  std::pair<s21::map<int, int>::iterator, bool> res = aboba.insert(999, -1);

  ASSERT_FALSE(res.second);
  ASSERT_EQ(res.first, aboba.end());
  ASSERT_FALSE(aboba.contains(999));
}

TEST(test_map, insert_mapped_value_4) {
  s21::map<std::string, int> aboba;
  const int element_num = 10000;
  std::vector<std::string> key_container;
  std::string key = "key";

  for (int i = 0; i < element_num; ++i) {
    key += std::to_string(i);
    key_container.push_back(key);
    aboba.insert({key, i});
    key = "key";
  }

  std::pair<s21::map<std::string, int>::iterator, bool> res =
      aboba.insert("key8999", -999999);

  ASSERT_TRUE(res.second);
  ASSERT_EQ(res.first->first, "key8999");
  ASSERT_EQ(res.first->second, -999999);
  ASSERT_TRUE(aboba.contains("key8999"));
}

TEST(test_map, insert_mapped_value_5) {
  s21::map<std::string, int> aboba;
  const int element_num = 10000;
  std::vector<std::string> key_container;
  std::string key = "key";

  for (int i = 0; i < element_num; ++i) {
    key += std::to_string(i);
    key_container.push_back(key);
    aboba.insert({key, i});
    key = "key";
  }

  std::pair<s21::map<std::string, int>::iterator, bool> res =
      aboba.insert("key9999", -999999);

  ASSERT_TRUE(res.second);
  ASSERT_EQ(res.first->first, "key9999");
  ASSERT_EQ(res.first->second, -999999);
  ASSERT_TRUE(aboba.contains("key9999"));
  ASSERT_EQ((--aboba.end())->second, -999999);

  res = aboba.insert("key0", -7777);

  ASSERT_TRUE(res.second);
  ASSERT_EQ(res.first->first, "key0");
  ASSERT_EQ(res.first->second, -7777);
  ASSERT_TRUE(aboba.contains("key0"));
  ASSERT_EQ(aboba.begin()->second, -7777);
}

TEST(test_map, insert_assign_1) {
  s21::map<std::string, int> aboba;
  const int element_num = 10000;
  std::vector<std::string> key_container;
  std::string key = "key";

  for (int i = 0; i < element_num; ++i) {
    key += std::to_string(i);
    key_container.push_back(key);
    aboba.insert({key, i});
    key = "key";
  }

  std::pair<s21::map<std::string, int>::iterator, bool> res =
      aboba.insert_or_assign("key8999", -999999);

  ASSERT_FALSE(res.second);
  ASSERT_EQ(res.first->first, "key8999");
  ASSERT_EQ(res.first->second, -999999);
  ASSERT_TRUE(aboba.contains("key8999"));
}

TEST(test_map, insert_assign_2) {
  s21::map<std::string, int> aboba;
  const int element_num = 10000;
  std::vector<std::string> key_container;
  std::string key = "key";

  for (int i = 0; i < element_num; ++i) {
    key += std::to_string(i);
    key_container.push_back(key);
    aboba.insert({key, i});
    key = "key";
  }

  std::pair<s21::map<std::string, int>::iterator, bool> res =
      aboba.insert_or_assign("key10001", -999999);

  ASSERT_TRUE(res.second);
  ASSERT_EQ(res.first->first, "key10001");
  ASSERT_EQ(res.first->second, -999999);
  ASSERT_TRUE(aboba.contains("key10001"));
}

TEST(test_map, insert_assign_3) {
  s21::map<int, int> aboba;

  ASSERT_TRUE(aboba.empty());
  ASSERT_EQ(aboba.size(), 0);

  std::pair<s21::map<int, int>::iterator, bool> res =
      aboba.insert_or_assign(-1, -999999);

  ASSERT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 1);

  ASSERT_TRUE(res.second);
  ASSERT_EQ(res.first->first, -1);
  ASSERT_EQ(res.first->second, -999999);
  ASSERT_TRUE(aboba.contains(-1));
}

TEST(test_map, insert_assign_4) {
  s21::map<int, int> aboba;

  ASSERT_TRUE(aboba.empty());
  ASSERT_EQ(aboba.size(), 0);

  aboba.insert_or_assign(-1, -999999);
  aboba.insert_or_assign(10, 10);
  aboba.insert_or_assign(15, 14);

  ASSERT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 3);

  ASSERT_EQ(aboba.begin()->first, -1);
  ASSERT_EQ(aboba.begin()->second, -999999);

  ASSERT_EQ((--aboba.end())->first, 15);
  ASSERT_EQ((--aboba.end())->second, 14);

  std::pair<s21::map<int, int>::iterator, bool> res =
      aboba.insert_or_assign(15, -999999);

  ASSERT_FALSE(res.second);
  ASSERT_EQ(res.first->second, -999999);
  ASSERT_EQ((--aboba.end())->second, -999999);
}

TEST(test_map, insert_assign_5) {
  s21::map<int, std::string> aboba;

  ASSERT_TRUE(aboba.empty());
  ASSERT_EQ(aboba.size(), 0);

  aboba.insert_or_assign(-1, "googoober");
  aboba.insert_or_assign(10, "glob");
  aboba.insert_or_assign(15, "slaanesh");

  ASSERT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 3);

  ASSERT_EQ(aboba.begin()->first, -1);
  ASSERT_EQ(aboba.begin()->second, "googoober");

  ASSERT_EQ((--aboba.end())->first, 15);
  ASSERT_EQ((--aboba.end())->second, "slaanesh");

  std::pair<s21::map<int, std::string>::iterator, bool> res =
      aboba.insert_or_assign(15, "finn");

  ASSERT_FALSE(res.second);
  ASSERT_EQ(res.first->second, "finn");
  ASSERT_EQ((--aboba.end())->second, "finn");
}

TEST(test_map, erase_1) {
  s21::map<int, int> aboba{{1, 1}, {2, 1}};
  ASSERT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 2);

  auto it = aboba.erase(aboba.begin());

  ASSERT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 1);
  ASSERT_EQ(it->first, 2);
}

TEST(test_map, erase_2) {
  s21::map<int, int> aboba{{1, 1}, {2, 1}};
  aboba.erase(aboba.end());

  ASSERT_FALSE(aboba.empty());
  ASSERT_EQ(aboba.size(), 2);
}

TEST(test_map, erase_3) {
  s21::map<int, int> test_clean_container{{1, 1}, {2, 1}, {3, 1}};
  auto it = test_clean_container.erase(test_clean_container.begin());

  it = test_clean_container.erase(it);
  it = test_clean_container.erase(it);

  ASSERT_TRUE(test_clean_container.empty());
  ASSERT_EQ(test_clean_container.size(), 0);
}

TEST(test_map, erase_4) {
  s21::map<int, int> byond{{1, 1}, {50, 10}, {15, 13}, {60, 30}, {2, 30}};

  auto it = byond.begin();

  byond.erase(it);

  ASSERT_EQ(byond.begin()->first, 2);

  it = byond.end();
  --it;
  byond.erase(it);

  ASSERT_EQ((--byond.end())->first, 50);
}

TEST(test_map, erase_5) {
  s21::map<int, int> midle{{1, 1}, {50, 10}, {15, 13}, {60, 30}, {2, 30}};

  auto it = midle.begin();

  ++it;
  ++it;

  it = midle.erase(it);

  ASSERT_EQ(it->first, 50);

  std::vector<int> in_container_expect{1, 2, 50, 60};
  it = midle.begin();
  auto _end = midle.end();

  for (int i = 0; it != _end; ++it, ++i) {
    ASSERT_EQ(it->first, in_container_expect[i]);
  }
}

TEST(test_map, erase_6) {
  s21::map<int, int> midle{{1, 1}, {50, 10}, {15, 13}, {60, 30}, {2, 30}};

  auto it = midle.begin();

  ++it;
  ++it;

  it = midle.erase(it);

  ASSERT_EQ(it->first, 50);
  using iterator_map = s21::map<int, int>::iterator;

  std::pair<iterator_map, bool> res = midle.insert({90, 1});

  EXPECT_TRUE(res.second);

  std::vector<int> in_container_expect{1, 2, 50, 60, 90};
  it = midle.begin();
  auto _end = midle.end();

  for (int i = 0; it != _end; ++it, ++i) {
    ASSERT_EQ(it->first, in_container_expect[i]);
  }
}

TEST(test_map, erase_7) {
  s21::map<int, int> midle{{1, 1}, {50, 10}, {15, 13}, {60, 30}, {2, 30}};

  auto it = midle.begin();

  ++it;
  ++it;

  it = midle.erase(it);

  ASSERT_EQ(it->first, 50);
  using iterator_map = s21::map<int, int>::iterator;

  std::pair<iterator_map, bool> res = midle.insert({90, 1});

  EXPECT_TRUE(res.second);

  it = res.first;

  midle.erase(it);

  std::vector<int> in_container_expect{1, 2, 50, 60};
  it = midle.begin();
  auto _end = midle.end();

  for (int i = 0; it != _end; ++it, ++i) {
    ASSERT_EQ(it->first, in_container_expect[i]);
  }
}

TEST(test_map, erase_8) {
  s21::map<std::string, std::string> boba{
      {"nature", "caller"}, {"killer", "logger"}, {"abobaer", "cucumber"},
      {"kooler", "xorer"},  {"forse", "majore"},  {"alpha", "hope"}};
  s21::map<std::string, std::string> mergeble{
      {"Alpha", "1"},   {"Beta", "2"},   {"Gamma", "3"},    {"Delta", "4"},
      {"Epsilon", "5"}, {"Zeta", "6"},   {"Eta", "7"},      {"Theta", "8"},
      {"Iota", "9"},    {"Kappa", "10"}, {"Lambda", "11"},  {"Mu", "12"},
      {"Nu", "13"},     {"Xi", "14"},    {"Omicron", "15"}, {"Pi", "16"},
      {"Rho", "17"},    {"Sigma", "18"}, {"Tau", "19"},     {"Upsilon", "20"},
      {"Phi", "21"},    {"Chi", "22"},   {"Psi", "23"},     {"Omega", "24"}};
  s21::map<std::string, std::string> nothing;
  s21::map<std::string, std::string> one_late{{"a", "c"}};

  s21::map<std::string, std::string> two{{"goal", "shit"},
                                         {"crimson", "curse"}};

  s21::map<std::string, s21::map<std::string, std::string>> aboba{
      {"cucumber", boba},
      {"flubert", mergeble},
      {"hope", nothing},
      {"last", one_late},
      {"goal", two}};

  auto it = aboba.begin();

  for (; it != aboba.end();) {
    it = aboba.erase(it);
  }

  ASSERT_TRUE(aboba.empty());
  ASSERT_EQ(aboba.size(), 0);
}

TEST(test_map, swap_1) {
  s21::map<int, int> base{{1, 1}, {50, 10}, {15, 13}, {60, 30}, {2, 30}};

  s21::map<int, int> swaper;

  EXPECT_TRUE(swaper.empty());
  EXPECT_EQ(swaper.size(), 0);

  swaper.swap(base);

  ASSERT_FALSE(swaper.empty());
  EXPECT_EQ(swaper.size(), 5);

  ASSERT_TRUE(base.empty());
  EXPECT_EQ(base.size(), 0);

  swaper.swap(base);

  ASSERT_FALSE(base.empty());
  EXPECT_EQ(base.size(), 5);
  ASSERT_TRUE(swaper.empty());
  EXPECT_EQ(swaper.size(), 0);
}

TEST(test_map, swap_2) {
  s21::map<int, int> base;

  s21::map<int, int> swaper;

  EXPECT_TRUE(base.empty());
  EXPECT_EQ(base.size(), 0);
  EXPECT_TRUE(swaper.empty());
  EXPECT_EQ(swaper.size(), 0);

  swaper.swap(base);

  ASSERT_TRUE(swaper.empty());
  EXPECT_EQ(swaper.size(), 0);
  ASSERT_TRUE(base.empty());
  EXPECT_EQ(base.size(), 0);
}

TEST(test_map, merge_1) {
  s21::map<int, int> base;
  s21::map<int, int> mergeble;

  EXPECT_TRUE(base.empty());
  EXPECT_EQ(base.size(), 0);
  EXPECT_TRUE(mergeble.empty());
  EXPECT_EQ(mergeble.size(), 0);

  base.merge(mergeble);

  EXPECT_TRUE(base.empty());
  EXPECT_EQ(base.size(), 0);
  EXPECT_TRUE(mergeble.empty());
  EXPECT_EQ(mergeble.size(), 0);
}

TEST(test_map, merge_2) {
  s21::map<int, int> base{{1, 1}, {90, 1}, {3, 3}, {5, 4}, {10, 30}};
  s21::map<int, int> mergeble{{1, 1}, {90, 1}, {3, 3}, {5, 4}, {10, 30}};

  base.merge(mergeble);

  EXPECT_EQ(base.size(), 5);
  EXPECT_EQ(mergeble.size(), 5);

  auto it_b = base.begin();
  auto it_m = mergeble.begin();

  for (int i = 0; i < int(base.size()); ++it_b, ++it_m, ++i) {
    ASSERT_EQ(it_b->first, it_m->first);
  }
}

TEST(test_map, merge_3) {
  s21::map<int, int> base{{1, 1}, {90, 1}, {3, 3}, {5, 4}, {10, 30}};
  s21::map<int, int> mergeble;

  base.merge(mergeble);

  EXPECT_EQ(base.size(), 5);
  EXPECT_EQ(mergeble.size(), 0);
}

TEST(test_map, merge_4) {
  s21::map<int, int> base{{1, 1}, {90, 1}, {3, 3}, {5, 4}, {10, 30}};
  s21::map<int, int> mergeble{{1, 2}, {91, 1}, {4, 5},
                              {6, 3}, {11, 2}, {10, 30}};

  base.merge(mergeble);

  EXPECT_EQ(base.size(), 9);
  EXPECT_EQ(mergeble.size(), 2);

  auto it_b = base.begin();
  auto it_m = mergeble.begin();
  std::vector<int> i_expect{1, 3, 4, 5, 6, 10, 11, 90, 91};
  std::vector<int> i_expect_2{1, 10};

  for (size_t i = 0; it_b != base.end() && i < i_expect.size(); ++it_b, ++i) {
    ASSERT_EQ(it_b->first, i_expect[i]);
  }

  for (size_t i = 0; it_m != mergeble.end() && i < i_expect_2.size();
       ++it_m, ++i) {
    ASSERT_EQ(it_m->first, i_expect_2[i]);
  }
}

TEST(test_map, merge_5) {
  s21::map<int, int> base{{1, 1}, {90, 1}, {3, 3}, {5, 4}, {10, 30}};
  s21::map<int, int> mergeble{{91, 1}, {4, 5}, {6, 3}, {11, 2}};

  base.merge(mergeble);

  EXPECT_EQ(base.size(), 9);
  EXPECT_TRUE(mergeble.empty());
  EXPECT_EQ(mergeble.size(), 0);

  auto it_b = base.begin();
  std::vector<int> i_expect{1, 3, 4, 5, 6, 10, 11, 90, 91};

  for (size_t i = 0; it_b != base.end() && i < i_expect.size(); ++it_b, ++i) {
    ASSERT_EQ(it_b->first, i_expect[i]);
  }
}

TEST(test_map, merge_6) {
  s21::map<std::string, int> base{
      {"alpha", 1},   {"beta", 2}, {"gamma", 3},  {"delta", 4}, {"epsilon", 5},
      {"zeta", 6},    {"eta", 7},  {"theta", 8},  {"iota", 9},  {"kappa", 10},
      {"lambda", 11}, {"mu", 12},  {"nu", 13},    {"xi", 14},   {"omicron", 15},
      {"pi", 16},     {"rho", 17}, {"sigma", 18}, {"tau", 19},  {"upsilon", 20},
      {"phi", 21},    {"chi", 22}, {"psi", 23},   {"omega", 24}};

  s21::map<std::string, int> mergeble{
      {"Alpha", 1},   {"Beta", 2}, {"Gamma", 3},  {"Delta", 4}, {"Epsilon", 5},
      {"Zeta", 6},    {"Eta", 7},  {"Theta", 8},  {"Iota", 9},  {"Kappa", 10},
      {"Lambda", 11}, {"Mu", 12},  {"Nu", 13},    {"Xi", 14},   {"Omicron", 15},
      {"Pi", 16},     {"Rho", 17}, {"Sigma", 18}, {"Tau", 19},  {"Upsilon", 20},
      {"Phi", 21},    {"Chi", 22}, {"Psi", 23},   {"Omega", 24}};

  base.merge(mergeble);

  ASSERT_FALSE(base.empty());
  ASSERT_TRUE(mergeble.empty());

  ASSERT_EQ(base.size(), 48);
}

TEST(test_map, merge_7) {
  s21::map<std::string, int> base{
      {"alpha", 1},   {"beta", 2}, {"gamma", 3},  {"delta", 4}, {"epsilon", 5},
      {"zeta", 6},    {"eta", 7},  {"theta", 8},  {"iota", 9},  {"kappa", 10},
      {"lambda", 11}, {"mu", 12},  {"nu", 13},    {"xi", 14},   {"omicron", 15},
      {"pi", 16},     {"rho", 17}, {"sigma", 18}, {"tau", 19},  {"upsilon", 20},
      {"phi", 21},    {"chi", 22}, {"psi", 23},   {"omega", 24}};

  s21::map<std::string, int> mergeble{
      {"Alpha", 1},   {"Beta", 2}, {"Gamma", 3},  {"delta", 4}, {"epsilon", 5},
      {"Zeta", 6},    {"Eta", 7},  {"Theta", 8},  {"Iota", 9},  {"Kappa", 10},
      {"Lambda", 11}, {"Mu", 12},  {"Nu", 13},    {"Xi", 14},   {"omicron", 15},
      {"Pi", 16},     {"Rho", 17}, {"Sigma", 18}, {"Tau", 19},  {"Upsilon", 20},
      {"Phi", 21},    {"Chi", 22}, {"Psi", 23},   {"omega", 24}};

  base.merge(mergeble);

  ASSERT_FALSE(base.empty());
  ASSERT_FALSE(mergeble.empty());

  ASSERT_EQ(base.size(), 44);
  ASSERT_EQ(mergeble.size(), 4);

  mergeble.merge(base);

  ASSERT_FALSE(base.empty());
  ASSERT_FALSE(mergeble.empty());

  ASSERT_EQ(base.size(), 4);
  ASSERT_EQ(mergeble.size(), 44);

  s21::map<std::string, int> empty_con;

  ASSERT_TRUE(empty_con.empty());

  empty_con.merge(mergeble);

  ASSERT_TRUE(mergeble.empty());
  ASSERT_FALSE(empty_con.empty());
  ASSERT_EQ(empty_con.size(), 44);

  empty_con.merge(base);

  ASSERT_FALSE(base.empty());
  ASSERT_FALSE(empty_con.empty());
  ASSERT_EQ(empty_con.size(), 44);
  ASSERT_EQ(base.size(), 4);
}

TEST(test_map, merge_8) {
  s21::map<std::string, int> base{
      {"alpha", 1},   {"beta", 2}, {"gamma", 3},  {"delta", 4}, {"epsilon", 5},
      {"zeta", 6},    {"eta", 7},  {"theta", 8},  {"iota", 9},  {"kappa", 10},
      {"lambda", 11}, {"mu", 12},  {"nu", 13},    {"xi", 14},   {"omicron", 15},
      {"pi", 16},     {"rho", 17}, {"sigma", 18}, {"tau", 19},  {"upsilon", 20},
      {"phi", 21},    {"chi", 22}, {"psi", 23},   {"omega", 24}};

  s21::map<std::string, int> mergeble{
      {"Alpha", 1},   {"Beta", 2}, {"Gamma", 3},  {"Delta", 4}, {"Epsilon", 5},
      {"Zeta", 6},    {"Eta", 7},  {"Theta", 8},  {"Iota", 9},  {"Kappa", 10},
      {"Lambda", 11}, {"Mu", 12},  {"nu", 13},    {"Xi", 14},   {"Omicron", 15},
      {"Pi", 16},     {"Rho", 17}, {"Sigma", 18}, {"Tau", 19},  {"Upsilon", 20},
      {"Phi", 21},    {"Chi", 22}, {"Psi", 23},   {"Omega", 24}};

  base.merge(mergeble);

  ASSERT_FALSE(base.empty());
  ASSERT_FALSE(mergeble.empty());

  ASSERT_EQ(base.size(), 47);
  ASSERT_EQ(mergeble.size(), 1);
}

TEST(test_map, merge_9) {
  s21::map<std::string, int> base{
      {"alpha", 1},   {"beta", 2}, {"gamma", 3},  {"delta", 4}, {"epsilon", 5},
      {"zeta", 6},    {"eta", 7},  {"theta", 8},  {"iota", 9},  {"kappa", 10},
      {"lambda", 11}, {"mu", 12},  {"nu", 13},    {"xi", 14},   {"omicron", 15},
      {"pi", 16},     {"rho", 17}, {"sigma", 18}, {"tau", 19},  {"upsilon", 20},
      {"phi", 21},    {"chi", 22}, {"psi", 23},   {"omega", 24}};

  s21::map<std::string, int> mergeble{
      {"alpha", 1},   {"beta", 2}, {"gamma", 3},  {"delta", 4}, {"epsilon", 5},
      {"zeta", 6},    {"eta", 7},  {"theta", 8},  {"iota", 9},  {"kappa", 10},
      {"lambda", 11}, {"mu", 12},  {"nu", 13},    {"xi", 14},   {"omicron", 15},
      {"pi", 16},     {"rho", 12}, {"Sigma", 18}, {"tau", 19},  {"upsilon", 20},
      {"phi", 21},    {"chi", 22}, {"psi", 23},   {"omega", 24}};

  base.merge(mergeble);

  ASSERT_FALSE(base.empty());
  ASSERT_FALSE(mergeble.empty());

  ASSERT_EQ(base.size(), 25);
  ASSERT_EQ(mergeble.size(), 23);
}

TEST(test_map, contains_1) {
  s21::map<std::string, int> base{
      {"alpha", 1},   {"beta", 2}, {"gamma", 3},  {"delta", 4}, {"epsilon", 5},
      {"zeta", 6},    {"eta", 7},  {"theta", 8},  {"iota", 9},  {"kappa", 10},
      {"lambda", 11}, {"mu", 12},  {"nu", 13},    {"xi", 14},   {"omicron", 15},
      {"pi", 16},     {"rho", 17}, {"sigma", 18}, {"tau", 19},  {"upsilon", 20},
      {"phi", 21},    {"chi", 22}, {"psi", 23},   {"omega", 24}};

  s21::map<std::string, int> mergeble{
      {"alpha", 1},   {"beta", 2}, {"gamma", 3},  {"delta", 4}, {"epsilon", 5},
      {"zeta", 6},    {"eta", 7},  {"theta", 8},  {"iota", 9},  {"kappa", 10},
      {"lambda", 11}, {"mu", 12},  {"nu", 13},    {"xi", 14},   {"omicron", 15},
      {"pi", 16},     {"rho", 12}, {"Sigma", 18}, {"tau", 19},  {"upsilon", 20},
      {"phi", 21},    {"chi", 22}, {"psi", 23},   {"omega", 24}};

  base.merge(mergeble);

  ASSERT_FALSE(base.empty());
  ASSERT_FALSE(mergeble.empty());

  ASSERT_EQ(base.size(), 25);
  ASSERT_EQ(mergeble.size(), 23);

  ASSERT_FALSE(mergeble.contains("Sigma"));
  ASSERT_TRUE(mergeble.contains("rho"));
}

TEST(test_map, contains_2) {
  s21::map<std::string, int> base;

  base.insert({" Attempts", 1});
  base.insert({"to", 1});
  base.insert({"extract(splice)", 999});
  base.insert({"each", 1});
  base.insert({"element", 2});
  base.insert({"in", 1});
  base.insert({"source", 1});
  base.insert(
      {"and          insert it into *          this using the comparison "
       "object "
       "of * this.If there is an element in *          this with key "
       "equivalent "
       "to the key of an element from source, then that element is not "
       "extracted from source.No elements are copied ormoved,      only the "
       "internal pointers of the container nodes are              "
       "repointed.All "
       "pointers and          references to the transferred elements remain "
       "valid,but now refer into * this,not into source.          The behavior "
       "is undefined if get_allocator () !=source.get_allocator().",
       1});

  ASSERT_FALSE(base.empty());
  ASSERT_TRUE(base.contains(
      "and          insert it into *          this using the comparison object "
      "of * this.If there is an element in *          this with key equivalent "
      "to the key of an element from source, then that element is not "
      "extracted from source.No elements are copied ormoved,      only the "
      "internal pointers of the container nodes are              repointed.All "
      "pointers and          references to the transferred elements remain "
      "valid,but now refer into * this,not into source.          The behavior "
      "is undefined if get_allocator () !=source.get_allocator()."));
}

TEST(test_map, contains_3) {
  s21::map<std::string, int> base;
  s21::map<std::string, int> nothing;

  base.insert({" Attempts", 1});
  base.insert({"to", 1});
  base.insert({"extract(splice)", 999});
  base.insert({"each", 1});
  base.insert({"element", 2});
  base.insert({"in", 1});
  base.insert({"source", 1});
  base.insert(
      {"and          insert it into *          this using the comparison "
       "object "
       "of * this.If there is an element in *          this with key "
       "equivalent "
       "to the key of an element from source, then that element is not "
       "extracted from source.No elements are copied ormoved,      only the "
       "internal pointers of the container nodes are              "
       "repointed.All "
       "pointers and          references to the transferred elements remain "
       "valid,but now refer into * this,not into source.          The behavior "
       "is undefined if get_allocator () !=source.get_allocator().",
       1});

  s21::map<s21::map<std::string, int>, bool> map_map;

  map_map.insert({base, true});

  ASSERT_FALSE(base.empty());
  ASSERT_FALSE(map_map.empty());
  ASSERT_TRUE(base.contains(
      "and          insert it into *          this using the comparison object "
      "of * this.If there is an element in *          this with key equivalent "
      "to the key of an element from source, then that element is not "
      "extracted from source.No elements are copied ormoved,      only the "
      "internal pointers of the container nodes are              repointed.All "
      "pointers and          references to the transferred elements remain "
      "valid,but now refer into * this,not into source.          The behavior "
      "is undefined if get_allocator () !=source.get_allocator()."));
  ASSERT_TRUE(map_map.contains(base));
  ASSERT_FALSE(map_map.contains(nothing));
}

TEST(test_map, insert_many_1) {
  s21::map<int, int> aboba{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  aboba.insert_many(std::make_pair(5, 5), std::make_pair(6, 6),
                    std::make_pair(7, 7));
  auto it = aboba.end();
  --it;

  ASSERT_EQ(it->first, 7);
  --it;
  ASSERT_EQ(it->first, 6);
  --it;
  ASSERT_EQ(it->first, 5);
  --it;
  ASSERT_EQ(it->first, 4);
}

TEST(test_map, insert_many_2) {
  s21::map<int, int> aboba{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  s21::vector<std::pair<s21::map<int, int>::iterator, bool>> res =
      aboba.insert_many(std::make_pair(5, 5), std::make_pair(6, 6),
                        std::make_pair(7, 7));

  ASSERT_TRUE(res[0].second);
  ASSERT_TRUE(res[1].second);
  ASSERT_TRUE(res[2].second);

  auto it = res[0].first;
  --it;
  ASSERT_EQ(it->first, 4);
  ++it;
  ASSERT_EQ(it->first, 5);
  ++it;
  ASSERT_EQ(it->first, 6);
  ++it;
  ASSERT_EQ(it->first, 7);
}

TEST(test_map, insert_many_3) {
  s21::map<int, int> aboba{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  s21::vector<std::pair<s21::map<int, int>::iterator, bool>> res =
      aboba.insert_many();

  ASSERT_TRUE(res.empty());

  auto it = aboba.begin();
  ASSERT_EQ(it->first, 1);
  ++it;
  ASSERT_EQ(it->first, 2);
  ++it;
  ASSERT_EQ(it->first, 3);
  ++it;
  ASSERT_EQ(it->first, 4);
  ++it;
  ASSERT_EQ(it, aboba.end());
}

TEST(test_map, map_contain_1) {
  s21::map<int, int> glober{{1, 1},  {2, 3},    {-4, 5},
                            {-7, 9}, {100, 32}, {-500, 100}};
  s21::map<int, int> glober_1{{1, 1},  {2, 3},    {-4, 5},
                              {-7, 9}, {100, 32}, {-500, 100}};
  s21::map<int, int> glober_2{{1, 1},  {2, 3},    {-4, 5},
                              {-7, 9}, {100, 32}, {-500, 100}};
  s21::map<s21::map<int, int>, std::string> aboba{
      {glober, "aboba"}, {glober_1, "joka"}, {glober_2, "goga"}};
  auto it = aboba.begin();

  ASSERT_EQ(aboba.size(), 1);
  ASSERT_EQ(it->second, "aboba");
  ++it;

  ASSERT_EQ(it, aboba.end());
}

TEST(test_map, map_contain_2) {
  s21::map<int, int> glober{{1, 1},  {2, 3},    {-4, 5},
                            {-7, 9}, {100, 32}, {-500, 100}};
  s21::map<int, int> glober_1{{2, 1},  {4, 3},    {-4, 5},
                              {-7, 9}, {100, 32}, {-499, 100}};
  s21::map<int, int> glober_2{{3, 1},  {2, 3},    {-4, 5},
                              {-7, 9}, {100, 32}, {-501, 100}};
  s21::map<s21::map<int, int>, std::string> aboba{
      {glober, "aboba"}, {glober_1, "joka"}, {glober_2, "goga"}};
  auto it = aboba.begin();

  ASSERT_EQ(aboba.size(), 3);
  ASSERT_EQ(it->second, "goga");
  ++it;
  ASSERT_EQ(it->second, "aboba");
  ++it;
  ASSERT_EQ(it->second, "joka");
  ++it;
  ASSERT_EQ(it, aboba.end());
}