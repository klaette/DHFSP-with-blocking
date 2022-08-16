int On_wall_ineffective_collision(vector<vector<int>>&Seq, int &KE, int &buffer, double KELossRate, int &NumHit)
{
	//Find the critical factoy
	int Fpt = -1;
	int PE = 0;
	for (int f = 0; f < Seq.size(); f++)
	{
		int TempPE = GetFspan(Seq[f]);
		if (TempPE>PE)
		{
			PE = TempPE;
			Fpt = f;
		}
	}
	for (int i = 0; i < Seq[Fpt].size(); i++)
	{
		vector<vector<int>>TempSeq = Seq;
		int Job = Seq[Fpt][i];
		Seq[Fpt].erase(Seq[Fpt].begin() + i);
		int TempPE = Job_To_BestFactory_Bestposition(Job, Seq);
		if (PE + KE >= TempPE)
		{
			default_random_engine e(time(0));
			uniform_real_distribution<double> u(KELossRate, 1.0);

			KE = (PE + KE - TempPE)*u(e);
			buffer = buffer + KE*(1.0 - u(e));
			PE = TempPE;
			NumHit = 0;

			break;
		}
		else
		{
			NumHit++;
			Seq = TempSeq;
		}
	}
	return PE;
}

// Decomposition operator
void Decomposition(vector<vector<int>>&Seq, int &PE1, int &KE1, vector<vector<int>>&New_Seq, int &PE2, int &KE2, int &buffer, int &Flag)
{
	Flag = -1;
	// Create a seq to store the original seq
	vector<vector<int>>TempSeq = Seq;

	vector<vector<int>>LeftSeq;
	LeftSeq.resize(Seq.size());
	for (int i = 0; i < LeftSeq.size(); i++)
		LeftSeq[i].clear();

	vector<vector<int>>RightSeq;
	RightSeq.resize(Seq.size());
	for (int i = 0; i < RightSeq.size(); i++)
		RightSeq[i].clear();

	//select the cut point
	for (int f = 0; f < Seq.size(); f++)
	{
		int point = rand() % Seq[f].size();     //
		for (int j = 0; j < point; j++)
			LeftSeq[f].push_back(Seq[f][j]);
		for (int j = point; j < Seq[f].size(); j++)
			RightSeq[f].push_back(Seq[f][j]);
	}

	vector<vector<int>>TempLeftSeq = LeftSeq;

	int TempPE1 = 0;
	int TempPE2 = 0;
	for (int f = 0; f < RightSeq.size(); f++)
	{
		for (int i = 0; i < RightSeq[f].size(); i++)
			TempPE1 = Job_To_BestFactory_Bestposition(RightSeq[f][i], LeftSeq);
	}

	for (int f = 0; f < TempLeftSeq.size(); f++)
	{
		for (int i = 0; i < TempLeftSeq[f].size(); i++)
			TempPE2 = Job_To_BestFactory_Bestposition(TempLeftSeq[f][i], RightSeq);
	}

	if (PE1 + KE1 >= TempPE1 + TempPE2)
	{
		Seq = LeftSeq;
		New_Seq = RightSeq;

		default_random_engine e(time(0));
		uniform_real_distribution<double>q1(0, 1.0);
		KE1 = (PE1 + KE1 - TempPE1 - TempPE2)*q1(e);
		KE2 = (PE1 + KE1 - TempPE1 - TempPE2)*(1.0 - q1(e));
		PE1 = TempPE1;
		PE2 = TempPE2;
	}
	else if (PE1 + KE1 + buffer >= TempPE1 + TempPE2)
	{
		Seq = LeftSeq;
		New_Seq = RightSeq;

		default_random_engine e(time(0));
		uniform_real_distribution<double>q2(0, 1.0);
		uniform_real_distribution<double>q3(0, 1.0);
		uniform_real_distribution<double>q4(0, 1.0);
		uniform_real_distribution<double>q5(0, 1.0);

		int InitialPE1 = PE1;
		int InitialKE1 = KE1;

		KE1 = (PE1 + KE1 - TempPE1 - TempPE2 + buffer)*q2(e)*q3(e);
		KE2 = (PE1 + KE1 - TempPE1 - TempPE2 + buffer)*q4(e)*q5(e);

		buffer = InitialPE1 + InitialKE1 - TempPE1 - TempPE2 + buffer - KE1 - KE2;

		PE1 = TempPE1;
		PE2 = TempPE2;
	}
	else
		Flag = 0;
}

void Intermolecular_ineffective_collision(vector<vector<int>>&Seq1, int &PE1, int &KE1, int &NumHit1, vector<vector<int>>&Seq2, int &PE2, int &KE2, int &NumHit2)
{
	//Create a seq to store the jobs from destruction phase
	vector<int>DestructionSeq1;
	DestructionSeq1.clear();

	vector<int>DestructionSeq2 = DestructionSeq1;

	//Create two seqs to store two original seqs
	vector<vector<int>>TempSeq1 = Seq1;
	vector<vector<int>>TempSeq2 = Seq2;
	int TempPE1 = 0;
	int TempPE2 = 0;

	//the number of jobs obtained from the destruction phase
	int Low = gFactory;
	int High = gJobs / 2;
	int Des_Num_Job1 = Low + rand() % (High - Low + 1);
	int Des_Num_Job2 = Low + rand() % (High - Low + 1);

	for (int f = 0; f < Seq1.size(); f++)
	{
		
		int Jobpt = rand() % Seq1[f].size();
		DestructionSeq1.push_back(Seq1[f][Jobpt]);
		Seq1[f].erase(Seq1[f].begin() + Jobpt);
	}

	for (int f = 0; f < Seq2.size(); f++)
	{
	
		int Jobpt = rand() % Seq2[f].size();
		DestructionSeq2.push_back(Seq2[f][Jobpt]);
		Seq2[f].erase(Seq2[f].begin() + Jobpt);
	}

	while (DestructionSeq1.size() < Des_Num_Job1)   //
	{
		int Fpt = rand() % Seq1.size();
		if (Seq1[Fpt].size()>1)
		{
			int Jobpt = rand() % Seq1[Fpt].size();
			DestructionSeq1.push_back(Seq1[Fpt][Jobpt]);
			Seq1[Fpt].erase(Seq1[Fpt].begin() + Jobpt);
		}
	}

	while (DestructionSeq2.size() < Des_Num_Job2)     //
	{
		int Fpt = rand() % Seq2.size();
		if (Seq2[Fpt].size() > 1)
		{
			int Jobpt = rand() % Seq2[Fpt].size();
			DestructionSeq2.push_back(Seq2[Fpt][Jobpt]);
			Seq2[Fpt].erase(Seq2[Fpt].begin() + Jobpt);
		}
	}

	for (int i = 0; i < DestructionSeq1.size(); i++)
	{
		int Job = DestructionSeq1[i];
		TempPE1 = Job_To_BestFactory_Bestposition(Job, Seq1);
	}

	for (int i = 0; i < DestructionSeq2.size(); i++)
	{
		int Job = DestructionSeq2[i];
		TempPE2 = Job_To_BestFactory_Bestposition(Job, Seq2);
	}

	if (PE1 + KE1 + PE2 + KE2 >= TempPE1 + TempPE2)
	{
		default_random_engine e(time(0));
		uniform_real_distribution<double>q6(0, 1.0);
		KE1 = (PE1 + KE1 + PE2 + KE2 - TempPE1 - TempPE2)*q6(e);
		KE2 = (PE1 + KE1 + PE2 + KE2 - TempPE1 - TempPE2)*(1.0 - q6(e));

		PE1 = TempPE1;
		PE2 = TempPE2;

		NumHit1 = 0;
		NumHit2 = 0;
	}
	else
	{
		Seq1 = TempSeq1;
		Seq2 = TempSeq2;

		NumHit1++;
		NumHit2++;
	}
}

void Synthesis(vector<vector<int>>&Seq1, int &PE1, int &KE1, vector<vector<int>>&Seq2, int &PE2, int &KE2, int &Flag)
{
	Flag = -1;

	vector<vector<int>>LeftSeq;
	LeftSeq.resize(Seq1.size());
	for (int i = 0; i < LeftSeq.size(); i++)
		LeftSeq[i].clear();

	//Create a seq to store Seq2
	vector<vector<int>>TempSeq2 = Seq2;


	//select the cut point
	for (int f = 0; f < Seq1.size(); f++)
	{
		int point = rand() % Seq1[f].size();     //
		for (int j = 0; j < point; j++)
			LeftSeq[f].push_back(Seq1[f][j]);
	}

	vector<int>LeftSeq_Job;
	LeftSeq_Job.clear();
	for (int f = 0; f < LeftSeq.size(); f++)
	{
		for (int i = 0; i < LeftSeq[f].size(); i++)
			LeftSeq_Job.push_back(LeftSeq[f][i]);
	}

	//delete the jobs in Seq2 which is stored in leftSeq
	for (int j = 0; j < LeftSeq_Job.size(); j++)
	{
		int TempJob = LeftSeq_Job[j];
		for (int f = 0; f < Seq2.size(); f++)
		{
			for (int i = 0; i < Seq2[f].size(); i++)
			{
				if (TempJob == Seq2[f][i])
					Seq2[f].erase(Seq2[f].begin() + i);
			}
		}
	}

	//combine the leftSeq with the partial Seq2
	for (int f = 0; f < LeftSeq.size(); f++)
	{
		for (int i = 0; i < Seq2[f].size(); i++)
			LeftSeq[f].push_back(Seq2[f][i]);
	}

	int TempPE = GetFspan(LeftSeq);
	if (PE1 + KE1 + PE2 + KE2 >= TempPE)
	{
		KE1 = PE1 + KE1 + PE2 + KE2 - TempPE;
		PE1 = TempPE;
		Seq1 = LeftSeq;
		Flag = 0;
	}
	else
		Seq2 = TempSeq2;
}

//Find the best individual

int FindBestIndividual(vector<int>PopulationSpan)
{
	int TempSpan = INT_MAX;
	int BestIndividual = -1;
	for (int i = 0; i < PopulationSpan.size(); i++)
	{
		if (PopulationSpan[i] < TempSpan)
		{
			TempSpan = PopulationSpan[i];
			BestIndividual = i;
		}
	}
	return BestIndividual;
}

int CRO(long TimeLimit, int InitialKE, double KELossRate, int Deth, int Syth)  //Deth decomposition threshold // Syth  synthesis threshold
{
	long InitialTime = GetElapsedProcessTime();

	//Initialization
	double MoleColl = 0.5;
	int buffer = 0;
	int PSize = 10;

	vector<int>KE;
	KE.resize(PSize, InitialKE);

	vector<vector<vector<int>>>Populattion;
	Populattion.resize(PSize);

	vector<int>PE;
	PE.resize(PSize, 0);

	for (int i = 0; i < PSize - 1; i++)
		PE[i] = NEH2_Rand(Populattion[i]);

	PE[PSize - 1] = NEH2(Populattion[PSize - 1]);

	vector<int>NumHit;
	NumHit.resize(Populattion.size(), 0);

	int MinHit = 0;

	while (GetElapsedProcessTime() - InitialTime < TimeLimit)
	{
		//		cout << "enter" << endl;
		//create a random number between 0 and 1
		default_random_engine e(time(0));
		uniform_real_distribution<double>b(0, 1.0);

		if ((b(e) > MoleColl) || (Populattion.size() == 1))
		{
			int BestIndividual = -1;
			BestIndividual = FindBestIndividual(PE);
			MinHit = NumHit[BestIndividual];

			int Individual = rand() % Populattion.size();
			if (NumHit[Individual] - MinHit > Deth)
			{
				int Flag = -1;
				int PE2 = 0;
				int KE2 = 0;
				vector<vector<int>>New_Seq;
				//				cout << "Decomposition" << endl;
				Decomposition(Populattion[Individual], PE[Individual], KE[Individual], New_Seq, PE2, KE2, buffer, Flag);

				if (Flag == 0)
					NumHit[Individual]++;
				else
				{
					Populattion.push_back(New_Seq);
					PE.push_back(PE2);
					KE.push_back(KE2);
					NumHit[Individual] = 0;
					NumHit.push_back(0);
				}
			}
			else
			{
				//				cout << "On_wall_ineffective_collision" << endl;
				PE[Individual] = On_wall_ineffective_collision(Populattion[Individual], KE[Individual], buffer, KELossRate, NumHit[Individual]);
			}
		}
		else
		{
			//Randomly select two molecules from population
			int Individual1 = rand() % Populattion.size();
			int Individual2 = -1;
			do
			{
				Individual2 = rand() % Populattion.size();
			} while (Individual1 == Individual2);

			if ((KE[Individual1] <= Syth) && (KE[Individual2] <= Syth))
			{
				int Flag = -1;
				//				cout << "Synthesis" << endl;
				Synthesis(Populattion[Individual1], PE[Individual1], KE[Individual1], Populattion[Individual2], PE[Individual2], KE[Individual2], Flag);
				if (Flag == 0)
				{
					Populattion.erase(Populattion.begin() + Individual2);
					PE.erase(PE.begin() + Individual2);
					KE.erase(KE.begin() + Individual2);
					NumHit[Individual1] = 0;
					NumHit.erase(NumHit.begin() + Individual2);
				}
				else
				{
					NumHit[Individual1]++;
					NumHit[Individual2]++;
				}
			}
			else
			{
				//				cout << "Intermolecular_ineffective_collision" << endl;
				Intermolecular_ineffective_collision(Populattion[Individual1], PE[Individual1], KE[Individual1], NumHit[Individual1], Populattion[Individual2], PE[Individual2], KE[Individual2], NumHit[Individual2]);
			}
		}
	}
	//for (int i = 0; i < Populattion.size(); i++)
	//	CheckChrom(Populattion[i], PE[i]);
	int minimum = INT_MAX;
	for (int i = 0; i < Populattion.size(); i++)
	{
		int BestIndividual = GetFspan(Populattion[i]);/*FindBestIndividual(PE);*/
		if (BestIndividual < minimum)
		{
			minimum = BestIndividual;
		}
	}
	
	return minimum;
}

void CRO_Run(int CPU, int Ins)
{
	int InitialKE = 150;
	double KELossRate = 0.7;
	int  Deth = 10;
	int	Syth = 50;

	const int Reps = 5;
	vector<int> TValueArray(Reps);

	Read(Ins);
	long TimeLimit = CPU * gMachine*gJobs;
	for (int rep = 0; rep < Reps; rep++)
	{
		long start = ::GetElapsedProcessTime();
		srand(Ins * 100 + rep);
		int TValue = CRO(TimeLimit, InitialKE, KELossRate, Deth, Syth);

		cout << "\t" << Ins << "\t" << gFactory << "\t" << gJobs << "\t" << gMachine << "\t" << TValue << "\t" << (::GetElapsedProcessTime() - start) / 1000.0 << endl;
		TValueArray[rep] = TValue;
	}

	ostringstream str;
	str << "CRO_" << CPU << "_" << Ins << ".txt";
	ofstream ofile;
	ofile.open(str.str());

	for (int rep = 0; rep < Reps; rep++)
	{
		ofile << TValueArray[rep] << "\t";
	}

	ofile.close();
}

int CRO_Compared_Curve(long TimeLimit, int InitialKE, double KELossRate, int Deth, int Syth, int LocalValue, long LocalTime, int No)  //Deth decomposition threshold // Syth  synthesis threshold
{
	long InitialTime = GetElapsedProcessTime();

	//Initialization
	double MoleColl = 0.5;
	int buffer = 0;
	int PSize = 10;

	//建立一个txt文件
	ostringstream str;
	str << "Test_CRO_Curve_Ins=" << No << ".txt";                //
	ofstream ofile;
	ofile.open(str.str());

	vector<int>KE;
	KE.resize(PSize, InitialKE);

	vector<vector<vector<int>>>Populattion;
	Populattion.resize(PSize);

	vector<int>PE;
	PE.resize(PSize, 0);

	for (int i = 0; i < PSize - 1; i++)
		PE[i] = NEH2_Rand(Populattion[i]);

	PE[PSize - 1] = NEH2(Populattion[PSize - 1]);

	vector<int>NumHit;
	NumHit.resize(Populattion.size(), 0);

	int MinHit = 0;



	int minimum01 = INT_MAX;
	for (int i = 0; i < Populattion.size(); i++)
	{
		int BestIndividual = GetFspan(Populattion[i]);/*FindBestIndividual(PE);*/
		if (BestIndividual < minimum01)
		{
			minimum01 = BestIndividual;
		}
	}
	LocalValue = minimum01;                             //
	LocalTime = GetElapsedProcessTime() - InitialTime;         //
	ofile << LocalTime << "\t" << LocalValue << "\t" << endl;
	minimum01 = INT_MAX;
	
	while (GetElapsedProcessTime() - InitialTime < TimeLimit)
	{
		//		cout << "enter" << endl;
		//create a random number between 0 and 1
		default_random_engine e(time(0));
		uniform_real_distribution<double>b(0, 1.0);

		if ((b(e) > MoleColl) || (Populattion.size() == 1))
		{
			int BestIndividual = -1;
			BestIndividual = FindBestIndividual(PE);
			MinHit = NumHit[BestIndividual];

			int Individual = rand() % Populattion.size();
			if (NumHit[Individual] - MinHit > Deth)
			{
				int Flag = -1;
				int PE2 = 0;
				int KE2 = 0;
				vector<vector<int>>New_Seq;
				//				cout << "Decomposition" << endl;
				Decomposition(Populattion[Individual], PE[Individual], KE[Individual], New_Seq, PE2, KE2, buffer, Flag);

				if (Flag == 0)
					NumHit[Individual]++;
				else
				{
					Populattion.push_back(New_Seq);
					PE.push_back(PE2);
					KE.push_back(KE2);
					NumHit[Individual] = 0;
					NumHit.push_back(0);
				}
			}
			else
			{
				//				cout << "On_wall_ineffective_collision" << endl;
				PE[Individual] = On_wall_ineffective_collision(Populattion[Individual], KE[Individual], buffer, KELossRate, NumHit[Individual]);
			}

		
		}
		else
		{
			//Randomly select two molecules from population
			int Individual1 = rand() % Populattion.size();
			int Individual2 = -1;
			do
			{
				Individual2 = rand() % Populattion.size();
			} while (Individual1 == Individual2);

			if ((KE[Individual1] <= Syth) && (KE[Individual2] <= Syth))
			{
				int Flag = -1;
				//				cout << "Synthesis" << endl;
				Synthesis(Populattion[Individual1], PE[Individual1], KE[Individual1], Populattion[Individual2], PE[Individual2], KE[Individual2], Flag);
				if (Flag == 0)
				{
					Populattion.erase(Populattion.begin() + Individual2);
					PE.erase(PE.begin() + Individual2);
					KE.erase(KE.begin() + Individual2);
					NumHit[Individual1] = 0;
					NumHit.erase(NumHit.begin() + Individual2);
				}
				else
				{
					NumHit[Individual1]++;
					NumHit[Individual2]++;
				}
			}
			else
			{
				//				cout << "Intermolecular_ineffective_collision" << endl;
				Intermolecular_ineffective_collision(Populattion[Individual1], PE[Individual1], KE[Individual1], NumHit[Individual1], Populattion[Individual2], PE[Individual2], KE[Individual2], NumHit[Individual2]);
			}
		}

		
		for (int i = 0; i < Populattion.size(); i++)
		{
			int BestIndividual = GetFspan(Populattion[i]);/*FindBestIndividual(PE);*/
			if (BestIndividual < minimum01)
			{
				minimum01 = BestIndividual;

			}
		}

		LocalValue = minimum01;                             //
		LocalTime = GetElapsedProcessTime() - InitialTime;         //
		ofile << LocalTime << "\t" << LocalValue << "\t" << endl;
	}
	ofile.close();
	
	//for (int i = 0; i < Populattion.size(); i++)
	//	CheckChrom(Populattion[i], PE[i]);
	int minimum = INT_MAX;
	int num;
	for (int i = 0; i < Populattion.size(); i++)
	{
		int BestIndividual = GetFspan(Populattion[i]);/*FindBestIndividual(PE);*/
		if (BestIndividual < minimum)
		{
			minimum = BestIndividual;
			num = i;
		}
	}
	GetFspan01(Populattion[num]);
	return minimum;
}