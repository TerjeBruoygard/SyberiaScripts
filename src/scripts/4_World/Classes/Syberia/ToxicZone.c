class ToxicZone
{
	vector m_position;
	float m_radius;
	string m_color;
};

class ToxicZoneView
{
	static const float SPAWN_PARTICLE_DISTANCE = 600;
	static const float DESPAWN_PARTICLE_DISTANCE = 650;
	static const float SMOKE_EFFECT_SIZE = 50;
	
	private ref array<Particle> m_particles;
	
	vector m_position;
	float m_radius;
	int m_particleId;
	
	void ToxicZoneView(vector pos, float radius, string color)
	{
		m_particles = new array<Particle>;
		m_position = pos;
		m_radius = radius;
		
		if (color == "green") m_particleId = ParticleList.SYBERIA_SMOKE_TOXIC_PARTICLE_GREEN;
		else if (color == "black") m_particleId = ParticleList.SYBERIA_SMOKE_TOXIC_PARTICLE_BLACK;
		else if (color == "gray") m_particleId = ParticleList.SYBERIA_SMOKE_TOXIC_PARTICLE_GREY;
		else if (color == "blue") m_particleId = ParticleList.SYBERIA_SMOKE_TOXIC_PARTICLE_BLUE;
		else if (color == "red") m_particleId = ParticleList.SYBERIA_SMOKE_TOXIC_PARTICLE_RED;
		else if (color == "yellow") m_particleId = ParticleList.SYBERIA_SMOKE_TOXIC_PARTICLE_YELLOW;
		else m_particleId = ParticleList.SYBERIA_SMOKE_TOXIC_PARTICLE_WHITE;
	}
	
	void Update(PlayerBase player)
	{
		if (!player)
			return;
		
		vector ppos = player.GetPosition();
		float distance = vector.Distance(ppos, m_position);
		if (distance < SPAWN_PARTICLE_DISTANCE + m_radius && m_particles.Count() == 0)
		{
			SpawnParticles();
		}
		else if (distance > DESPAWN_PARTICLE_DISTANCE + m_radius && m_particles.Count() > 0)
		{
			DestroyParticles();
		}
	}
	
	void SpawnParticles()
	{
		vector pos = "0 0 0";
		int r;
		float a;
		float yOffset = m_position[1] - GetGame().SurfaceY(m_position[0], m_position[2]);
		
		m_particles.Insert(Particle.PlayInWorld(m_particleId, m_position));
		
		r = SMOKE_EFFECT_SIZE;
		while (r < m_radius)
		{
			float circle_length = Math.PI2 * r;
			int points_count = (int)(circle_length / SMOKE_EFFECT_SIZE);
			float points_offset = Math.PI2 / points_count;
			
			a = 0.0;
			while (a < Math.PI2)
			{
				pos[0] = m_position[0] + (r * Math.Cos(a));
				pos[2] = m_position[2] + (r * Math.Sin(a));
				pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + yOffset;
				
				m_particles.Insert(Particle.PlayInWorld(m_particleId, pos));
				a = a + points_offset;
			}
			
			r = r + SMOKE_EFFECT_SIZE;
		}
	}
	
	void DestroyParticles()
	{
		foreach (Particle p : m_particles)
		{
			p.Stop();
		}
		m_particles.Clear();
	}
	
	void ~ToxicZoneView()
	{
		DestroyParticles();
	}
};