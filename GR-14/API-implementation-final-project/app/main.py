from fastapi import FastAPI
from app.controllers import monitor, profile
from app.core.database import Base, engine

app = FastAPI()

# Crear las tablas en la base de datos
Base.metadata.create_all(bind=engine)

# Registrar los controladores
app.include_router(monitor.router, prefix="/monitor", tags=["Monitor"])
app.include_router(profile.router, prefix="/profile", tags=["Profile"])
