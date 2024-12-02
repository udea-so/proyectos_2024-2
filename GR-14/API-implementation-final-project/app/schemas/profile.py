from pydantic import BaseModel
from datetime import datetime

class ProfileCreate(BaseModel):
    function_name: str
    module_name: str

class ProfileResponse(ProfileCreate):
    id: int
    profile_data: str
    timestamp: datetime

    class Config:
        orm_mode = True
